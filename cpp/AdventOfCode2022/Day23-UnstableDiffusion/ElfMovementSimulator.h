#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>
#include <boost/optional.hpp>

#include <unordered_set>
#include <deque>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day23
{

class ElfMovementSimulator
{
public:
    ElfMovementSimulator(const std::vector<std::string>& initialPositions);

    void simulate(unsigned numMaxRoundsToSimulate = 0);

    unsigned getNumGroundTilesInBoundingRectangle() const;
    unsigned getNumFirstRoundWhereNoElfMoves() const;

private:
    using Coordinates = std::pair<int, int>;

    const Coordinates SOUTH = {0, 1};
    const Coordinates NORTH = {0, -1};
    const Coordinates EAST = {1, 0};
    const Coordinates WEST = {-1, 0};

    std::unordered_set<Coordinates, boost::hash<Coordinates>> m_occupiedPositions;
    std::deque<Coordinates> m_proposedDirectionsInOrder{NORTH, SOUTH, WEST, EAST};
    unsigned m_numRoundsSimulated = 0;

    bool simulateRound();

    boost::optional<Coordinates> getProposedPosition(const Coordinates& currentPosition) const;
    bool areAllNeighborPositionsFree(const Coordinates& currentPosition) const;
    bool areAllPositionsFree(const std::vector<Coordinates>& positions) const;
    bool isFreeTowardsProposedDirection(const Coordinates& currentPosition, const Coordinates& proposedDirection) const;
};

}
}
}
