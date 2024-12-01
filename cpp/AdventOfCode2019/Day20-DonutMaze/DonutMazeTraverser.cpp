#include "DonutMazeTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day20
{

struct DonutMazeSearchNodeHash
{
    std::size_t operator()(const DonutMazeSearchNode& node) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, node.coordinates);
        boost::hash_combine(seed, node.layer);

        return seed;
    }
};

DonutMazeTraverser::DonutMazeTraverser(DonutMaze donutMaze, TraverseMode traverseMode)
    : m_maze{std::move(donutMaze)}
    , m_traverseMode{traverseMode}
{

}

void DonutMazeTraverser::traverse()
{
    std::queue<DonutMazeSearchNode> bfsQueue;
    DonutMazeSearchNode initialNode{m_maze.start, 0};
    bfsQueue.push(initialNode);

    std::unordered_set<DonutMazeSearchNode, DonutMazeSearchNodeHash> visited;
    visited.insert(initialNode);

    while (!bfsQueue.empty())
    {
        DonutMazeSearchNode currentNode = bfsQueue.front();
        bfsQueue.pop();

        if (hasReachedGoal(currentNode))
        {
            m_shortestPathLength = currentNode.numSteps;
            return;
        }

        std::vector<DonutMazeSearchNode> neighborNodes = createNeighborNodes(currentNode);

        for (auto& node : neighborNodes)
        {
            if (visited.find(node) == visited.cend())
            {
                visited.insert(node);
                bfsQueue.push(node);
            }
        }
    }

    throw std::runtime_error("Unable to find exit.");
}

int DonutMazeTraverser::getShortestPathLength() const
{
    return m_shortestPathLength;
}

std::vector<DonutMazeSearchNode> DonutMazeTraverser::createNeighborNodes(const DonutMazeSearchNode& currentNode) const
{
    std::vector<DonutMazeSearchNode> neighborNodes;

    const auto portalFindResult = m_maze.portalToDestination.find(currentNode.coordinates);
    if (portalFindResult != m_maze.portalToDestination.cend())
    {
        int layerModifier = getLayerModifier(currentNode.coordinates);
        int newLayer = currentNode.layer + layerModifier;
        if (m_traverseMode == TraverseMode::IGNORE_LAYERS || newLayer >= 0)
        {
            neighborNodes.push_back({DonutMazeSearchNode{portalFindResult->second, newLayer, currentNode.numSteps + 1}});
        }
    }

    std::vector<Coordinates> neighborCoordinates = getNeighborCoordinates(currentNode.coordinates);
    for (auto& coord : neighborCoordinates)
    {
        if (m_maze.map.at(coord.second).at(coord.first) == '.')
        {
            neighborNodes.push_back(DonutMazeSearchNode{std::move(coord), currentNode.layer, currentNode.numSteps + 1});
        }
    }

    return neighborNodes;
}

std::vector<Coordinates> DonutMazeTraverser::getNeighborCoordinates(const Coordinates& currentCoordinates) const
{
    std::vector<Coordinates> neighborCoordinates;
    neighborCoordinates.push_back({currentCoordinates.first + 1, currentCoordinates.second});
    neighborCoordinates.push_back({currentCoordinates.first - 1, currentCoordinates.second});
    neighborCoordinates.push_back({currentCoordinates.first, currentCoordinates.second + 1});
    neighborCoordinates.push_back({currentCoordinates.first, currentCoordinates.second - 1});
    return neighborCoordinates;
}

bool DonutMazeTraverser::hasReachedGoal(const DonutMazeSearchNode& node) const
{
    if (node.coordinates == m_maze.end)
    {
        if (m_traverseMode == TraverseMode::RESPECT_LAYERS && node.layer != 0)
        {
            return false;
        }

        return true;
    }

    return false;
}

int DonutMazeTraverser::getLayerModifier(const Coordinates& coordinates) const
{
    bool isOnOuterRing = coordinates.first == 2 ||
        coordinates.first == m_maze.map.at(coordinates.second).size() - 3 ||
        coordinates.second == 2 ||
        coordinates.second == m_maze.map.size() - 3;

    if (isOnOuterRing)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

}
}
}
