#include "OrbitMap.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day06
{

void OrbitMap::addEdge(NodeIDType from, NodeIDType to, EdgeType edgeType)
{
    if (edgeType == EdgeType::UNDIRECTED)
    {
        m_nodeIDToAdjacentNodeIDs[to].push_back(from);
    }

    m_nodeIDToAdjacentNodeIDs[std::move(from)].push_back(std::move(to));
}

unsigned OrbitMap::getNumTransitiveOrbits() const
{
    return getNumTransitiveOrbitsRecursive(CENTER_OF_MASS, 0);
}

unsigned OrbitMap::getDistanceBetweenStartAndGoal() const
{
    std::unordered_set<NodeIDType> visited;
    visited.insert(START);

    std::queue<NodeIDAndDistance> nextNodeQueue;
    nextNodeQueue.push({START, 0});

    while (!nextNodeQueue.empty())
    {
        NodeIDAndDistance currentNodeIDAndDistance = nextNodeQueue.front();
        nextNodeQueue.pop();

        if (currentNodeIDAndDistance.nodeID == GOAL)
        {
            return currentNodeIDAndDistance.distance;
        }

        for (const auto& neighborNodeID : m_nodeIDToAdjacentNodeIDs.at(currentNodeIDAndDistance.nodeID))
        {
            if (visited.find(neighborNodeID) == visited.cend())
            {
                visited.insert(neighborNodeID);
                nextNodeQueue.push({neighborNodeID, currentNodeIDAndDistance.distance + 1});
            }
        }
    }

    throw std::runtime_error("No path found");
}

unsigned OrbitMap::getNumTransitiveOrbitsRecursive(const NodeIDType& startNodeID, unsigned numAncestors) const
{
    const auto adjacentNodeIDsFindResult = m_nodeIDToAdjacentNodeIDs.find(startNodeID);

    if (adjacentNodeIDsFindResult == m_nodeIDToAdjacentNodeIDs.cend())
    {
        return numAncestors;
    }

    unsigned numTransitiveOrbitsFromThisNode = 0;

    for (const auto& adjacentNode : adjacentNodeIDsFindResult->second)
    {
        numTransitiveOrbitsFromThisNode += getNumTransitiveOrbitsRecursive(adjacentNode, numAncestors + 1);
    }

    return numAncestors + numTransitiveOrbitsFromThisNode;
}

}
}
}
