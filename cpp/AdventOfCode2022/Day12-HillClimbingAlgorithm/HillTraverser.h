#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day12
{

const char START_POSITION_CHAR = 'S';
const char END_POSITION_CHAR = 'E';
const char HEIGHT_AT_START = 'a';
const char HEIGHT_AT_END = 'z';

using Heightmap = std::vector<std::string>;
using Coordinates = std::pair<int, int>;

class HillTraverser
{
public:
    HillTraverser(Heightmap heightmap, std::unordered_set<char> possibleStartChars);

    void traverse();

    int getMinStepsFromStartToEnd() const;

private:
    struct BfsNode
    {
        Coordinates coordinates;
        int numSteps;
    };

    Heightmap m_heightmap;
    size_t m_height;
    size_t m_width;
    std::vector<Coordinates> m_allPossibleStartCoordinates;
    Coordinates m_endCoordinates;

    int m_minStepsFromStartToEnd = std::numeric_limits<int>::max();

    void traverseFromSingleStartingPoint(const Coordinates& startCoordinates);

    std::vector<Coordinates> getAllReachableNeighborCoordinates(const Coordinates& baseCoordinates) const;
    bool isNeighborReachableFromNode(const Coordinates& baseCoordinates, const Coordinates& neighborCoordinates) const;
    bool isInBounds(const Coordinates& coordinates) const;
    const char& heightAt(const Coordinates& coordinates) const;
    char& heightAt(const Coordinates& coordinates);
};

}
}
}
