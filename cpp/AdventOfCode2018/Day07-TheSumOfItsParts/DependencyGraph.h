#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <set>
#include <unordered_map>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day07
{

using NodeIDType = char;
using OrderedNodeIDs = std::set<NodeIDType, std::greater<NodeIDType>>;
using UnorderedNodeIDs = std::unordered_set<NodeIDType>;

class DependencyGraph
{
public:
    void addEdge(NodeIDType from, NodeIDType to);

    std::string getTopologicalOrder() const;
    std::set<NodeIDType> getNodeIDsWithNoDependencies() const;
    bool isEmpty() const noexcept;

    void removeNode(NodeIDType nodeID);

private:
    std::unordered_map<NodeIDType, OrderedNodeIDs> m_nodeIDToDependentNodeIDs;
    std::unordered_map<NodeIDType, UnorderedNodeIDs> m_nodeIDsToDependencyNodeIDs;
    OrderedNodeIDs m_allNodesOrdered;

    void dfsFillOutFinishedNodes(const NodeIDType& startNodeID, std::unordered_set<NodeIDType>& visitedNodes, std::vector<NodeIDType>& finishedNodes) const;
};

}
}
}
