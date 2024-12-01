#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <vector>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int CHAMBER_WIDTH = 7;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day17
{

enum class Direction
{
    LEFT,
    RIGHT,
};

enum class RockType
{
    HYPHEN = 0,
    PLUS = 1,
    MIRRORED_L = 2,
    PILLAR = 3,
    SQUARE = 4,
};

using Coordinates = std::pair<int, int>;
using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

class Rock
{
public:
    Rock(RockType type, const Coordinates& bottomLeftCornerPosition);

    bool applyJet(Direction direction, const CoordinatesSet& occupiedCoordinates);
    bool applyFallUnit(const CoordinatesSet& occupiedCoordinates);

    const std::vector<Coordinates>& getAllCoordinates() const;

private:
    std::vector<Coordinates> m_allCoordinates;

    void inializeHyphenRock(const Coordinates& bottomLeftCornerPosition);
    void initializePlusRock(const Coordinates& bottomLeftCornerPosition);
    void initializeMirroredLRock(const Coordinates& bottomLeftCornerPosition);
    void initializePillarRock(const Coordinates& bottomLeftCornerPosition);
    void initializeSquareRock(const Coordinates& bottomLeftCornerPosition);
    void initializeRock(const Coordinates& bottomLeftCornerPosition, const std::vector<Coordinates>& allRelativeStartingCoordinates);

    bool applyOffset(const Coordinates& offset, const CoordinatesSet& occupiedCoordinates);

    static bool isValidMove(std::vector<Coordinates>& allCoordinatesAfterMove, const CoordinatesSet& occupiedCoordinates);
};

class FallingRockSimulator
{
public:
    FallingRockSimulator(std::vector<Direction> jetPattern, uint64_t numRocksToSimulate);

    void simulate();

    int64_t getTowerHeight() const;

private:
    struct State
    {
        std::array<int, CHAMBER_WIDTH> highestPointYCoordinatesRelativeToHeight;
        RockType nextRock;
        unsigned jetPatternIndex;

        unsigned numRocksSettled;

        bool operator==(const State& other) const
        {
            return highestPointYCoordinatesRelativeToHeight == other.highestPointYCoordinatesRelativeToHeight &&
                nextRock == other.nextRock &&
                jetPatternIndex == other.jetPatternIndex;
        }
    };

    struct StateHash
    {
        std::size_t operator()(const State& state) const
        {
            std::size_t seed = 0;

            boost::hash_combine(seed, state.highestPointYCoordinatesRelativeToHeight);
            boost::hash_combine(seed, state.nextRock);
            boost::hash_combine(seed, state.jetPatternIndex);

            return seed;
        }
    };

    std::vector<Direction> m_jetPattern;
    uint64_t m_numRocksToSimulate;

    CoordinatesSet m_occupiedPositions;
    size_t m_numPushesSimulated = 0;
    std::unordered_set<State, StateHash> m_seenStates;
    std::vector<int> m_numRocksSettledToTowerHeight;

    int64_t m_towerHeight;

    void settleRock(Rock rock);

    bool isColliding(const Rock& rock) const;
    int getMaxYCoordinate() const;
    std::array<int, CHAMBER_WIDTH> getHighestPointYCoordinatesRelativeToHeight() const;
    int64_t determineHeightAtTheEndOfSimulation(const State& cycleStartState, const State& cycleEndState) const;
};

}
}
}
