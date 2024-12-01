#include "BridgeGraph.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day24
{

BridgeGraph::BridgeGraph(NodeIDToNeighbors nodeIDToNeighbors) noexcept
    : m_nodeIDToNeighbors{std::move(nodeIDToNeighbors)}
{

}

unsigned BridgeGraph::maxCostWalk() const
{
    unsigned maxCost = 0;
    Walk maxCostLongestWalk{};

    traverseForMaxCostWalk(0, {}, 0, maxCost, Walk{}, maxCostLongestWalk);

    return maxCost;
}

unsigned BridgeGraph::maxCostLongestWalk() const
{
    unsigned maxCost = 0;
    Walk maxCostLongestWalk{};

    traverseForMaxCostWalk(0, {}, 0, maxCost, Walk{}, maxCostLongestWalk);

    return maxCostLongestWalk.cost;
}

void BridgeGraph::traverseForMaxCostWalk(NodeIDType currentNodeID, const VisitedEdgeSet& visitedEdgeSet, unsigned currentCost, unsigned& maxCost, const Walk& currentWalk, Walk& maxWalk) const
{
    NodeIDVector neighborIDs = m_nodeIDToNeighbors[currentNodeID];

    for (const NodeIDType neighborID : neighborIDs)
    {
        const Edge e{std::min(currentNodeID, neighborID), std::max(currentNodeID, neighborID)};

        if (visitedEdgeSet.find(e) == visitedEdgeSet.cend())
        {
            auto visitedEdgeSetExtended{visitedEdgeSet};
            visitedEdgeSetExtended.insert(e);

            const unsigned newCurrentCost = currentCost + currentNodeID + neighborID;
            maxCost = std::max(maxCost, newCurrentCost);

            const Walk newWalk{currentWalk.length + 1, newCurrentCost};
            maxWalk = std::max(maxWalk, newWalk);

            traverseForMaxCostWalk(neighborID, visitedEdgeSetExtended, newCurrentCost, maxCost, newWalk, maxWalk);
        }
    }
}

}
}
}
