#include "MultiDimensionalGameOfLifeSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day17
{

MultiDimensionalGameOfLifeSimulator::MultiDimensionalGameOfLifeSimulator(std::vector<MultiDimensionalVector> allStartingActiveCoordinates)
{
    for (auto& startingActiveCoordinates : allStartingActiveCoordinates)
    {
        m_activeCoordinatesSet.insert(std::move(startingActiveCoordinates));
    }
}

void MultiDimensionalGameOfLifeSimulator::simulateRounds(size_t numRounds)
{
    for (size_t i = 0; i < numRounds; ++i)
    {
        simulateRound();
    }
}

int MultiDimensionalGameOfLifeSimulator::getNumActiveCoordinates() const
{
    return m_activeCoordinatesSet.size();
}

void MultiDimensionalGameOfLifeSimulator::simulateRound()
{
    std::unordered_set<MultiDimensionalVector, MultiDimensionalVectorHash> nextRoundActiveCoordinatesSet;

    for (const auto& coordinates : getAllRelevantCoordinatesForNextRound())
    {
        if (isCoordinateActiveInNextRound(coordinates))
        {
            nextRoundActiveCoordinatesSet.insert(coordinates);
        }
    }

    m_activeCoordinatesSet = nextRoundActiveCoordinatesSet;
}

std::unordered_set<MultiDimensionalVector, MultiDimensionalVectorHash> MultiDimensionalGameOfLifeSimulator::getAllRelevantCoordinatesForNextRound() const
{
    std::unordered_set<MultiDimensionalVector, MultiDimensionalVectorHash> allRelevantCoordinatesForNextRound;

    for (const auto& activeCoordinates : m_activeCoordinatesSet)
    {
        allRelevantCoordinatesForNextRound.insert(activeCoordinates);

        std::vector<MultiDimensionalVector> allNeighborCoordinates = getAllNeighborCoordinates(activeCoordinates);
        for (const auto& neighborCoordinates : allNeighborCoordinates)
        {
            allRelevantCoordinatesForNextRound.insert(neighborCoordinates);
        }
    }

    return allRelevantCoordinatesForNextRound;
}

bool MultiDimensionalGameOfLifeSimulator::isCoordinateActiveInNextRound(const MultiDimensionalVector& coordinates) const
{
    const bool isCurrentlyActive = (m_activeCoordinatesSet.find(coordinates) != m_activeCoordinatesSet.cend());
    const int numActiveNeighbors = getNumActiveNeighbors(coordinates);

    const bool isActiveRemainingActive = isCurrentlyActive && (numActiveNeighbors == 2 || numActiveNeighbors == 3);
    const bool isInactiveBecomingActive = !isCurrentlyActive && numActiveNeighbors == 3;

    return isActiveRemainingActive || isInactiveBecomingActive;
}

std::vector<MultiDimensionalVector> MultiDimensionalGameOfLifeSimulator::getAllNeighborCoordinates(const MultiDimensionalVector& coordinates) const
{
    std::vector<MultiDimensionalVector> allNeighborCoordinates;

    getAllNeighborCoordinatesRecursive(coordinates, coordinates, 0, allNeighborCoordinates);

    return allNeighborCoordinates;
}

void MultiDimensionalGameOfLifeSimulator::getAllNeighborCoordinatesRecursive(const MultiDimensionalVector& originCoordinates,
                                        const MultiDimensionalVector& neighborCandidateCoordinates,
                                        size_t currentDimension,
                                        std::vector<MultiDimensionalVector>& result) const
{
    if (currentDimension == originCoordinates.size())
    {
        if (originCoordinates != neighborCandidateCoordinates)
        {
            result.push_back(neighborCandidateCoordinates);
        }
        return;
    }

    for (int i = originCoordinates[currentDimension] - 1; i <= originCoordinates[currentDimension] + 1; ++i)
    {
        auto neighborCandidateCoordinatesCopy{neighborCandidateCoordinates};
        neighborCandidateCoordinatesCopy[currentDimension] = i;
        getAllNeighborCoordinatesRecursive(originCoordinates, neighborCandidateCoordinatesCopy, currentDimension + 1, result);
    }
}

int MultiDimensionalGameOfLifeSimulator::getNumActiveNeighbors(const MultiDimensionalVector& coordinates) const
{
    std::vector<MultiDimensionalVector> allNeighborCoordinates = getAllNeighborCoordinates(coordinates);
    return std::count_if(allNeighborCoordinates.cbegin(), allNeighborCoordinates.cend(), [this](const auto& coords)
                            {
                                return this->m_activeCoordinatesSet.find(coords) != this->m_activeCoordinatesSet.cend();
                            });
}

}
}
}
