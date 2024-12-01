#include "FallingRockSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int ROCK_SPAWN_OFFSET_FROM_LEFT_OF_CHAMBER = 2;
const int ROCK_SPAWN_OFFSET_FROM_TOP_OF_ROCKS = 4;
const unsigned NUM_ROCK_TYPES = 5;

}


namespace AdventOfCode
{
namespace Year2022
{
namespace Day17
{

Rock::Rock(RockType type, const Coordinates& bottomLeftCornerPosition)
{
    switch (type)
    {
        case RockType::HYPHEN:
            inializeHyphenRock(bottomLeftCornerPosition);
            break;
        case RockType::PLUS:
            initializePlusRock(bottomLeftCornerPosition);
            break;
        case RockType::MIRRORED_L:
            initializeMirroredLRock(bottomLeftCornerPosition);
            break;
        case RockType::PILLAR:
            initializePillarRock(bottomLeftCornerPosition);
            break;
        case RockType::SQUARE:
            initializeSquareRock(bottomLeftCornerPosition);
            break;
        default:
            throw std::runtime_error("Invalid rock  type: " + std::to_string(static_cast<int>(type)));
    }
}

bool Rock::applyJet(Direction direction, const CoordinatesSet& occupiedCoordinates)
{
    if (direction == Direction::LEFT)
    {
        return applyOffset({-1, 0}, occupiedCoordinates);
    }
    else if (direction == Direction::RIGHT)
    {
        return applyOffset({1, 0}, occupiedCoordinates);
    }
}

bool Rock::applyFallUnit(const CoordinatesSet& occupiedCoordinates)
{
    return applyOffset({0, -1}, occupiedCoordinates);
}

const std::vector<Coordinates>& Rock::getAllCoordinates() const
{
    return m_allCoordinates;
}

void Rock::inializeHyphenRock(const Coordinates& bottomLeftCornerPosition)
{
    const std::vector<Coordinates> offsets = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    initializeRock(bottomLeftCornerPosition, offsets);
}

void Rock::initializePlusRock(const Coordinates& bottomLeftCornerPosition)
{
    const std::vector<Coordinates> offsets = {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}};
    initializeRock(bottomLeftCornerPosition, offsets);
}

void Rock::initializeMirroredLRock(const Coordinates& bottomLeftCornerPosition)
{
    const std::vector<Coordinates> offsets = {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}};
    initializeRock(bottomLeftCornerPosition, offsets);
}

void Rock::initializePillarRock(const Coordinates& bottomLeftCornerPosition)
{
    const std::vector<Coordinates> offsets = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    initializeRock(bottomLeftCornerPosition, offsets);
}

void Rock::initializeSquareRock(const Coordinates& bottomLeftCornerPosition)
{
    const std::vector<Coordinates> offsets = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    initializeRock(bottomLeftCornerPosition, offsets);
}

void Rock::initializeRock(const Coordinates& bottomLeftCornerPosition, const std::vector<Coordinates>& allRelativeStartingCoordinates)
{
    m_allCoordinates = allRelativeStartingCoordinates;
    applyOffset(bottomLeftCornerPosition, {});
}

bool Rock::applyOffset(const Coordinates& offset, const CoordinatesSet& occupiedCoordinates)
{
    std::vector<Coordinates> allCoordinatesAfterMove;

    for (auto& coordinates : m_allCoordinates)
    {
        allCoordinatesAfterMove.emplace_back(coordinates.first + offset.first, coordinates.second + offset.second);
    }

    if (isValidMove(allCoordinatesAfterMove, occupiedCoordinates))
    {
        m_allCoordinates = allCoordinatesAfterMove;
        return true;
    }
    else
    {
        return false;
    }
}

bool Rock::isValidMove(std::vector<Coordinates>& allCoordinatesAfterMove, const CoordinatesSet& occupiedCoordinates)
{
    return std::all_of(allCoordinatesAfterMove.cbegin(), allCoordinatesAfterMove.cend(), [occupiedCoordinates](const auto& coords)
                        {
                            const bool isInBounds = coords.first >= 0 && coords.first < CHAMBER_WIDTH && coords.second >= 0;
                            const bool isUnoccupied = occupiedCoordinates.find(coords) == occupiedCoordinates.cend();

                            return isInBounds && isUnoccupied;
                        });
}

FallingRockSimulator::FallingRockSimulator(std::vector<Direction> jetPattern, uint64_t numRocksToSimulate)
    : m_jetPattern{std::move(jetPattern)}
    , m_numRocksToSimulate{numRocksToSimulate}
{

}

void FallingRockSimulator::simulate()
{
    for (size_t numRocksSettled = 0; ; ++numRocksSettled)
    {
        const int maxY = getMaxYCoordinate();
        const int towerHeight = maxY + 1;
        m_numRocksSettledToTowerHeight.push_back(towerHeight);

        std::array<int, CHAMBER_WIDTH> highestPointYCoordinatesRelativeToHeight = getHighestPointYCoordinatesRelativeToHeight();
        const RockType nextRockType = static_cast<RockType>(numRocksSettled % NUM_ROCK_TYPES);
        const unsigned jetPatternIndex = m_numPushesSimulated % m_jetPattern.size();

        State currentState{std::move(highestPointYCoordinatesRelativeToHeight), nextRockType, jetPatternIndex, numRocksSettled};
        const auto insertionResult = m_seenStates.insert(currentState);

        // Cycle found
        if (!insertionResult.second)
        {
            m_towerHeight = determineHeightAtTheEndOfSimulation(*insertionResult.first, currentState);
            return;
        }

        const int spawnY = maxY + ROCK_SPAWN_OFFSET_FROM_TOP_OF_ROCKS;
        Rock rock{nextRockType, {ROCK_SPAWN_OFFSET_FROM_LEFT_OF_CHAMBER, spawnY}};

        settleRock(std::move(rock));
    }
}

int64_t FallingRockSimulator::getTowerHeight() const
{
    return m_towerHeight;
}

void FallingRockSimulator::settleRock(Rock rock)
{
    do
    {
        const Direction nextJetDirection = m_jetPattern.at(m_numPushesSimulated++ % m_jetPattern.size());
        rock.applyJet(nextJetDirection, m_occupiedPositions);
    } while (rock.applyFallUnit(m_occupiedPositions));

    const auto& allRockCoordinates = rock.getAllCoordinates();

    m_occupiedPositions.insert(allRockCoordinates.cbegin(), allRockCoordinates.cend());
}

bool FallingRockSimulator::isColliding(const Rock& rock) const
{
    const auto& rockCoordinates = rock.getAllCoordinates();

    return std::any_of(rockCoordinates.cbegin(), rockCoordinates.cend(), [this](const auto& coords)
                        {
                            return coords.second < 0 || this->m_occupiedPositions.find(coords) != this->m_occupiedPositions.cend();
                        });
}

int FallingRockSimulator::getMaxYCoordinate() const
{
    const auto maxYIter = std::max_element(m_occupiedPositions.cbegin(), m_occupiedPositions.cend(), [](const auto& lhs, const auto& rhs) {return lhs.second < rhs.second; });
    return maxYIter != m_occupiedPositions.cend() ? maxYIter->second : -1;
}

std::array<int, CHAMBER_WIDTH> FallingRockSimulator::getHighestPointYCoordinatesRelativeToHeight() const
{
    std::array<int, CHAMBER_WIDTH> highestPointYCoordinatesRelativeToHeight;
    highestPointYCoordinatesRelativeToHeight.fill(std::numeric_limits<int>::min());

    for (const auto& coordinates : m_occupiedPositions)
    {
        highestPointYCoordinatesRelativeToHeight.at(coordinates.first) = std::max(highestPointYCoordinatesRelativeToHeight.at(coordinates.first), coordinates.second);
    }

    const int maxY = *std::max_element(highestPointYCoordinatesRelativeToHeight.cbegin(), highestPointYCoordinatesRelativeToHeight.cend());

    for (auto& coordinate : highestPointYCoordinatesRelativeToHeight)
    {
        coordinate -= maxY;
    }

    return highestPointYCoordinatesRelativeToHeight;
}

int64_t FallingRockSimulator::determineHeightAtTheEndOfSimulation(const State& cycleStartState, const State& cycleEndState) const
{
    const unsigned cycleStartNumRocksSettled = cycleStartState.numRocksSettled;
    const unsigned cycleEndNumRocksSettled = cycleEndState.numRocksSettled;
    const unsigned cycleLength = cycleEndNumRocksSettled - cycleStartNumRocksSettled;

    const int cycleStartTowerHeight = m_numRocksSettledToTowerHeight.at(cycleStartNumRocksSettled);
    const int cycleEndTowerHeight = m_numRocksSettledToTowerHeight.at(cycleEndNumRocksSettled);
    const int cycleTowerHeightDelta = cycleEndTowerHeight - cycleStartTowerHeight;

    const uint64_t numRocksToSimulateAfterCycleStart = m_numRocksToSimulate - cycleStartNumRocksSettled;
    const uint64_t numFullCyclesInSimulation = numRocksToSimulateAfterCycleStart / cycleLength;

    const uint64_t finalCycleOffsetNumRocksSettledInSimulation = numRocksToSimulateAfterCycleStart % cycleLength;

    // The result here is actually the sum of two height deltas: the delta before the cycle starts, and the delta after the final cycle ends
    const int finalCycleOffsetTowerHeight = m_numRocksSettledToTowerHeight.at(cycleStartNumRocksSettled + finalCycleOffsetNumRocksSettledInSimulation);

    return numFullCyclesInSimulation * cycleTowerHeightDelta + finalCycleOffsetTowerHeight;
}

}
}
}
