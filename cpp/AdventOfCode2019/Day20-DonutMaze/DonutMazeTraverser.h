#pragma once

#include "DonutMazeParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day20
{

struct DonutMazeSearchNode
{
    Coordinates coordinates;
    int layer;
    int numSteps;

    bool operator==(const DonutMazeSearchNode& other) const
    {
        return coordinates == other.coordinates && layer == other.layer;
    }
};

enum class TraverseMode
{
    IGNORE_LAYERS,
    RESPECT_LAYERS,
};

class DonutMazeTraverser
{
public:
    DonutMazeTraverser(DonutMaze donutMaze, TraverseMode traverseMode = TraverseMode::IGNORE_LAYERS);

    void traverse();

    int getShortestPathLength() const;

private:
    DonutMaze m_maze;
    TraverseMode m_traverseMode;

    int m_shortestPathLength = std::numeric_limits<int>::max();

    std::vector<DonutMazeSearchNode> createNeighborNodes(const DonutMazeSearchNode& currentNode) const;
    std::vector<Coordinates> getNeighborCoordinates(const Coordinates& currentCoordinates) const;
    bool hasReachedGoal(const DonutMazeSearchNode& node) const;
    int getLayerModifier(const Coordinates& coordinates) const;
};

}
}
}
