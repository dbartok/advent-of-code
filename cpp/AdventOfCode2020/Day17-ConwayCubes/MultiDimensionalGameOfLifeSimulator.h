#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>
#include <boost/functional/hash/hash.hpp>

#include <vector>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day17
{

using MultiDimensionalVector = Eigen::Matrix<int, Eigen::Dynamic, 1>;

struct MultiDimensionalVectorHash
{
    size_t operator()(const MultiDimensionalVector& vector) const
    {
        size_t seed = 0;

        for (size_t i = 0; i < vector.size(); ++i)
        {
            boost::hash_combine(seed, vector[i]);
        }

        return seed;
    }
};

class MultiDimensionalGameOfLifeSimulator
{
public:
    MultiDimensionalGameOfLifeSimulator(std::vector<MultiDimensionalVector> allStartingActiveCoordinates);

    void simulateRounds(size_t numRounds);

    int getNumActiveCoordinates() const;

private:
    std::unordered_set<MultiDimensionalVector, MultiDimensionalVectorHash> m_activeCoordinatesSet;

    void simulateRound();

    std::unordered_set<MultiDimensionalVector, MultiDimensionalVectorHash> getAllRelevantCoordinatesForNextRound() const;
    bool isCoordinateActiveInNextRound(const MultiDimensionalVector& coordinates) const;
    std::vector<MultiDimensionalVector> getAllNeighborCoordinates(const MultiDimensionalVector& coordinates) const;
    void getAllNeighborCoordinatesRecursive(const MultiDimensionalVector& originCoordinates,
                                            const MultiDimensionalVector& neighborCandidateCoordinates,
                                            size_t currentDimension,
                                            std::vector<MultiDimensionalVector>& result) const;

    int getNumActiveNeighbors(const MultiDimensionalVector& coordinates) const;
};

}
}
}
