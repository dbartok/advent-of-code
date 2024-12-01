#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_set>
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const size_t NUM_DIMENSIONS = 3;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day18
{

using Coordinates = std::array<int, NUM_DIMENSIONS>;
using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

class LavaDropletAnalyzer
{
public:
    LavaDropletAnalyzer(std::vector<Coordinates> allLavaCubeCoordinates);

    unsigned getSurfaceArea() const;
    unsigned getOuterSurfaceArea() const;

private:
    CoordinatesSet m_allLavaCubeCoordinates;
    Coordinates m_lowerBound;
    Coordinates m_upperBound;

    std::vector<Coordinates> getInBoundsNeighborCoordinates(const Coordinates& coordinates) const;
    std::pair<Coordinates, Coordinates> getBounds() const;

    static std::vector<Coordinates> getAllNeighborCoordinates(const Coordinates& coordinates);
};

}
}
}
