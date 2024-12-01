#include "AmphipodOrganizer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <iterator>
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int ROOM_START_Y = 2;
const int ROOM_START_X = 3;
const char MIN_AMPHIPOD_CHAR = 'A';
const char MAX_AMPHIPOD_CHAR = 'D';
const char WALL_CHAR = '#';
const char EMPTY_SPACE_CHAR = '.';

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day23
{

using CoordinatesAndDistance = std::pair<Coordinates, int>;

State::State(Map map, unsigned totalCost)
    : m_map{std::move(map)}
    , m_totalCost{totalCost}
{

}

void State::move(const Coordinates& sourceCoordinates, const Coordinates& destinationCoordinates)
{
    std::swap(getValueAt(sourceCoordinates), getValueAt(destinationCoordinates));
}

void State::increaseCost(unsigned costDelta)
{
    m_totalCost += costDelta;
}

bool State::isAmphipod(const Coordinates& coordinates) const
{
    return getValueAt(coordinates) >= MIN_AMPHIPOD_CHAR && getValueAt(coordinates) <= MAX_AMPHIPOD_CHAR;
}

bool State::areAllAmphipodsOrganized() const
{
    for (char amphipodChar = MIN_AMPHIPOD_CHAR; amphipodChar <= MAX_AMPHIPOD_CHAR; ++amphipodChar)
    {
        if (!isAmphipodOrganized(amphipodChar))
        {
            return false;
        }
    }

    return true;
}

unsigned State::getSingleMoveCost(const Coordinates& coordinates) const
{
    if (!isAmphipod(coordinates))
    {
        throw std::runtime_error("Only amphipods have move costs");
    }

    const char amphipodChar = getValueAt(coordinates);

    return static_cast<unsigned>(pow(10, amphipodChar - MIN_AMPHIPOD_CHAR));
}

bool State::isValidDestination(const Coordinates& sourceCoordinates, const Coordinates& destinationCoordinates) const
{
    if (!isEmptySpace(destinationCoordinates))
    {
        return false;
    }

    if (isHallway(sourceCoordinates))
    {
        return isCorrectDestinationRoomCoordinates(sourceCoordinates, destinationCoordinates);
    }
    else
    {
        return isHallway(destinationCoordinates);
    }
}

bool State::isEmptySpace(const Coordinates& coordinates) const
{
    return getValueAt(coordinates) == EMPTY_SPACE_CHAR;
}

unsigned State::getTotalCost() const
{
    return m_totalCost;
}

const Map& State::getMap() const
{
    return m_map;
}

bool State::operator==(const State& other) const
{
    return m_map == other.m_map;
}

char& State::getValueAt(const Coordinates& coordinates)
{
    return const_cast<char&>(const_cast<const State&>(*this).getValueAt(coordinates));
}

bool State::isAmphipodOrganized(char amphipodChar) const
{
    return isAmphipodOrganizedStartingFrom(amphipodChar, ROOM_START_Y);
}

bool State::isHallway(const Coordinates& coordinates) const
{
    if (coordinates.second >= ROOM_START_Y)
    {
        return false;
    }

    for (char amphipodChar = MIN_AMPHIPOD_CHAR; amphipodChar <= MAX_AMPHIPOD_CHAR; ++amphipodChar)
    {
        const int amphipodRoomX = getAmphipodRoomX(amphipodChar);
        if (coordinates.first == amphipodRoomX)
        {
            return false;
        }
    }

    return true;
}

bool State::isCorrectDestinationRoomCoordinates(const Coordinates& sourceCoordinates, const Coordinates& destinationCoordinates) const
{
    const char amphipodChar = getValueAt(sourceCoordinates);
    const int amphipodRoomX = getAmphipodRoomX(amphipodChar);
    if (amphipodRoomX != destinationCoordinates.first)
    {
        return false;
    }

    return isAmphipodOrganizedStartingFrom(amphipodChar, destinationCoordinates.second + 1);
}

bool State::isAmphipodOrganizedStartingFrom(char amphipodChar, int amphipodRoomY) const
{
    const int amphipodRoomX = getAmphipodRoomX(amphipodChar);

    while (true)
    {
        if (getValueAt({amphipodRoomX, amphipodRoomY}) == WALL_CHAR)
        {
            return true;
        }

        if (getValueAt({amphipodRoomX, amphipodRoomY}) != amphipodChar)
        {
            return false;
        }

        ++amphipodRoomY;
    }
}

const char& State::getValueAt(const Coordinates& coordinates) const
{
    return m_map.at(coordinates.second).at(coordinates.first);
}


int State::getAmphipodRoomX(char amphipodChar)
{
    const int amphipodIndex = amphipodChar - MIN_AMPHIPOD_CHAR;
    return ROOM_START_X + 2 * amphipodIndex;
}

size_t hash_value(const State& state)
{
    boost::hash<Map> hasher;
    return hasher(state.getMap());
}

AmphipodOrganizer::AmphipodOrganizer(Map initialMap)
    : m_width{initialMap.at(0).size()}
    , m_height{initialMap.size()}
{
    m_visitedStates.insert({initialMap, 0});

    m_activeStates.insert({std::move(initialMap), 0});
}

void AmphipodOrganizer::organize()
{
    while (!m_activeStates.empty())
    {
        auto currentState = *m_activeStates.cbegin();
        m_activeStates.erase(m_activeStates.cbegin());

        // New best solution
        if (currentState.areAllAmphipodsOrganized())
        {
            m_minOrganizedStateCost = std::min(m_minOrganizedStateCost.get_value_or(std::numeric_limits<unsigned>::max()), currentState.getTotalCost());
        }
        // Bound
        else if (m_minOrganizedStateCost.has_value() && currentState.getTotalCost() > m_minOrganizedStateCost.value())
        {
            continue;
        }

        // Branch
        auto nextStates = generateNextStates(currentState);
        upsertNextStates(std::move(nextStates));
    }
}

unsigned AmphipodOrganizer::getMinEnergyUsed() const
{
    return m_minOrganizedStateCost.value();
}

void AmphipodOrganizer::upsertNextStates(std::vector<State> nextStates)
{
    for (auto& nextState : nextStates)
    {
        const auto findResult = m_visitedStates.find(nextState);
        if (findResult == m_visitedStates.end())
        {
            m_visitedStates.insert(nextState);

            m_activeStates.insert(std::move(nextState));
        }
        else if (findResult->getTotalCost() > nextState.getTotalCost())
        {
            m_visitedStates.erase(findResult);
            m_visitedStates.insert(nextState);

            m_activeStates.erase(nextState);
            m_activeStates.insert(std::move(nextState));
        }
    }
}

std::vector<State> AmphipodOrganizer::generateNextStates(const State& currentState) const
{
    std::vector<State> nextStates;

    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            if (!currentState.isAmphipod({i, j}))
            {
                continue;
            }

            std::vector<State> nextStatesFromStartCoordinates = generateNextStatesFromStartCoordinates(currentState, {i, j});
            nextStates.insert(nextStates.end(), std::make_move_iterator(nextStatesFromStartCoordinates.begin()), std::make_move_iterator(nextStatesFromStartCoordinates.end()));
        }
    }

    return nextStates;
}

std::vector<State> AmphipodOrganizer::generateNextStatesFromStartCoordinates(const State& currentState, const Coordinates& startCoordinates) const
{
    std::vector<State> nextStates;

    std::queue<CoordinatesAndDistance> bfsQueue{};
    bfsQueue.push({startCoordinates, 0});
    std::unordered_set<Coordinates, boost::hash<Coordinates>> visited{startCoordinates};

    while (!bfsQueue.empty())
    {
        auto currentCoordinatesAndDistance = bfsQueue.front();
        bfsQueue.pop();

        if (currentState.isValidDestination(startCoordinates, currentCoordinatesAndDistance.first))
        {
            State nextState{currentState};
            nextState.move(startCoordinates, currentCoordinatesAndDistance.first);
            nextState.increaseCost(currentCoordinatesAndDistance.second * currentState.getSingleMoveCost(startCoordinates));
            nextStates.push_back(std::move(nextState));
        }

        const std::vector<Coordinates> allNeighborCoordinates = getAllNeighborCoordinates(currentCoordinatesAndDistance.first);
        for (const auto& neighborCoordinates : allNeighborCoordinates)
        {
            if (!visited.insert(neighborCoordinates).second)
            {
                continue;
            }

            if (currentState.isEmptySpace(neighborCoordinates))
            {
                bfsQueue.push({neighborCoordinates, currentCoordinatesAndDistance.second + 1});
            }
        }
    }

    return nextStates;
}

std::vector<Coordinates> AmphipodOrganizer::getAllNeighborCoordinates(const Coordinates& coordinates)
{
    return
    {
        Coordinates{coordinates.first, coordinates.second - 1},
        Coordinates{coordinates.first, coordinates.second + 1},
        Coordinates{coordinates.first - 1, coordinates.second},
        Coordinates{coordinates.first + 1, coordinates.second}
    };
}

}
}
}
