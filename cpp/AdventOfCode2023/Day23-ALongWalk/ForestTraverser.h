#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_map>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day23
{

const char PATH = '.';
const char FOREST = '#';
const char UP_SLOPE = '^';
const char DOWN_SLOPE = 'v';
const char LEFT_SLOPE = '<';
const char RIGHT_SLOPE = '>';

using Coordinates = std::pair<int, int>;

const Coordinates UP = {0, -1};
const Coordinates DOWN = {0, 1};
const Coordinates LEFT = {-1, 0};
const Coordinates RIGHT = {1, 0};

struct CoordinatesAndDistance
{
    Coordinates coordinates;
    int distance;

    CoordinatesAndDistance(Coordinates coordinates, int distance)
        : coordinates{std::move(coordinates)}
        , distance{std::move(distance)}
    {

    }
};

struct LongestPathBfsNode
{
    int junctionIndex;
    int totalDistance;
    std::unordered_set<int> visited;

    LongestPathBfsNode(int junctionIndex, int totalDistance, std::unordered_set<int> visited)
        : junctionIndex{junctionIndex}
        , totalDistance{totalDistance}
        , visited{std::move(visited)}
    {

    }
};

class ForestTraverser
{
public:
    ForestTraverser(std::vector<std::string> map);

    void traverse();

    int getLongestPathLength() const;

private:
    const std::vector<std::string> m_map;
    const size_t m_width;
    const size_t m_height;
    const Coordinates m_start;
    const Coordinates m_end;

    int m_longestPathLength = 0;

    std::unordered_map<Coordinates, int, boost::hash<Coordinates>> m_junctionCoordinatesToIndex;

    std::vector<std::vector<int>> m_compactAdjacencyMatrix;

    void createCompactAdjacencyMatrix();
    void populateCompactAdjacencyMatrixForJunction(const Coordinates& startingJunctionCoordinates);

    std::vector<Coordinates> getAllJunctionCoordinates() const;
    std::vector<Coordinates> getAllNonForestNeighborCoordinates(const Coordinates& baseCoordinates) const;
    std::vector<Coordinates> getAllReachableNeighborCoordinates(const Coordinates& baseCoordinates) const;
    bool isInbounds(const Coordinates& coordinates) const;
    bool isValidStepFromBaseToNeighbor(const Coordinates& baseCoordinates, const Coordinates& neighborCoordinates) const;
    char getTileAt(const Coordinates& coordinates) const;
};

}
}
}
