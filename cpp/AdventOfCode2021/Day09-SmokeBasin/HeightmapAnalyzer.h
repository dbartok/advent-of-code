#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <algorithm>
#include <unordered_set>

#include <boost/functional/hash.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day09
{

using HeightmapRow = std::vector<int>;
using Heightmap = std::vector<HeightmapRow>;

using Coordinates = std::pair<int, int>;
using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

class HeightmapAnalyzer
{
public:
    HeightmapAnalyzer(Heightmap heightmap);

    int getSumOfRiskLevelsOfAllLowPoints() const;
    int getMultipleOfThreeLargestBasinSizes() const;

private:
    const Heightmap m_heightmap;

    const size_t m_width;
    const size_t m_height;

    std::vector<Coordinates> getAllLowPointCoordinates() const;
    bool isLowPoint(const Coordinates& coordinates) const;
    int getHeightAt(const Coordinates& coordinates) const;
    std::vector<Coordinates> getAllAdjacentLocationCoordinates(const Coordinates& baseCoordinates) const;
    bool isInBounds(const Coordinates& coordinates) const;
    std::vector<int> getBasinSizes() const;
    int getBasinSizeAt(const Coordinates& startCoordinates) const;
    int getBasinSizeAtRecursive(const Coordinates& startCoordinates, CoordinatesSet& visitedCoordinates) const;
};

}
}
}
