#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>
#include <boost/optional.hpp>

#include <vector>
#include <string>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day23
{

using MapRow = std::string;
using Map = std::vector<MapRow>;
using Coordinates = std::pair<int, int>;

class State
{
public:
    State(Map map, unsigned totalCost);

    void move(const Coordinates& sourceCoordinates, const Coordinates& destinationCoordinates);
    void increaseCost(unsigned costDelta);

    bool isAmphipod(const Coordinates& coordinates) const;
    bool areAllAmphipodsOrganized() const;
    unsigned getSingleMoveCost(const Coordinates& coordinates) const;
    bool isValidDestination(const Coordinates& sourceCoordinates, const Coordinates& destinationCoordinates) const;
    bool isEmptySpace(const Coordinates& coordinates) const;
    unsigned getTotalCost() const;
    const Map& getMap() const;

    bool operator==(const State& other) const;

private:
    Map m_map;
    unsigned m_totalCost;

    char& getValueAt(const Coordinates& coordinates);

    bool isAmphipodOrganized(char amphipodChar) const;
    bool isHallway(const Coordinates& coordinates) const;
    bool isCorrectDestinationRoomCoordinates(const Coordinates& sourceCoordinates, const Coordinates& destinationCoordinates) const;
    bool isAmphipodOrganizedStartingFrom(char amphipodChar, int amphipodRoomY) const;
    const char& getValueAt(const Coordinates& coordinates) const;

    static int getAmphipodRoomX(char amphipodChar);
};

size_t hash_value(const State& state);

class AmphipodOrganizer
{
public:
    AmphipodOrganizer(Map initialMap);

    void organize();

    unsigned getMinEnergyUsed() const;

private:
    std::unordered_set<State, boost::hash<State>> m_visitedStates;
    std::unordered_set<State, boost::hash<State>> m_activeStates;
    size_t m_width;
    size_t m_height;
    boost::optional<unsigned> m_minOrganizedStateCost;

    void upsertNextStates(std::vector<State> nextStates);

    std::vector<State> generateNextStates(const State& currentState) const;
    std::vector<State> generateNextStatesFromStartCoordinates(const State& currentState, const Coordinates& startCoordinates) const;

    static std::vector<Coordinates> getAllNeighborCoordinates(const Coordinates& coordinates);
};

}
}
}
