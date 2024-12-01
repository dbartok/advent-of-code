#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day21
{

using Coordinates = std::pair<int, int>;

class GardenTraverser
{
public:
    GardenTraverser(std::vector<std::string> map);

    void traverse(int numSteps);

    int getNumReachablePositions() const;

private:
    using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

    const std::vector<std::string> m_map;
    const size_t m_width;
    const size_t m_height;

    Coordinates m_startCoordinates;

    int m_numReachablePositions;

    std::vector<Coordinates> getAllReachableNeighborCoordinates(const Coordinates& baseCoordinates);

    char getSoilTypeAt(const Coordinates& coordinates) const;

    static int mod(int dividend, int divisor);
};

}
}
}
