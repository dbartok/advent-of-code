#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <vector>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day24
{

class BridgeGraph
{
public:
    using NodeIDType = unsigned;

    // Neighbors are stored as IDs in a vector
    using NodeIDVector = std::vector<NodeIDType>;

    // Neighbors are mapped to the nodes by their position in the vector
    using NodeIDToNeighbors = std::vector<NodeIDVector>;

    BridgeGraph(NodeIDToNeighbors nodeIDToNeighbors) noexcept;
    unsigned maxCostWalk() const;
    unsigned maxCostLongestWalk() const;

private:
    NodeIDToNeighbors m_nodeIDToNeighbors;

    using Edge = std::pair<NodeIDType, NodeIDType>;
    using VisitedEdgeSet = std::unordered_set<Edge, boost::hash<Edge>>;

    struct Walk
    {
        unsigned length;
        unsigned cost;

        Walk() noexcept
            : length{0}
            , cost{0}
        {

        }

        Walk(unsigned length, unsigned cost) noexcept
            : length{length}
            , cost{cost}
        {

        }

        bool operator<(const Walk& other) const noexcept
        {
            return std::tie(length, cost) < std::tie(other.length, other.cost);
        }
    };

    void traverseForMaxCostWalk(NodeIDType currentNodeID, const VisitedEdgeSet& visitedEdgeSet, unsigned currentCost, unsigned& maxCost, const Walk& currentWalk, Walk& maxWalk) const;
};

}
}
}
