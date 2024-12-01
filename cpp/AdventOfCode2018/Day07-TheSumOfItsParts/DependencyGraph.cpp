#pragma once

#include "DependencyGraph.h"

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day07
{

void DependencyGraph::addEdge(NodeIDType from, NodeIDType to)
{
    m_allNodesOrdered.insert(from);
    m_allNodesOrdered.insert(to);

    // Also register the destination node (without any edges)
    // to make sure we have a complete collection of all nodes
    m_nodeIDToDependentNodeIDs.emplace(to, OrderedNodeIDs{});
    m_nodeIDToDependentNodeIDs[std::move(from)].insert(std::move(to));

    m_nodeIDsToDependencyNodeIDs.emplace(from, UnorderedNodeIDs{});
    m_nodeIDsToDependencyNodeIDs[std::move(to)].insert(std::move(from));
}

std::string DependencyGraph::getTopologicalOrder() const
{
    std::vector<NodeIDType> finishedNodes;
    std::unordered_set<NodeIDType> visitedNodes;

    for (const auto& nodeID : m_allNodesOrdered)
    {
        if (visitedNodes.find(nodeID) == visitedNodes.end())
        {
            dfsFillOutFinishedNodes(nodeID, visitedNodes, finishedNodes);
        }
    }

    std::string topologicalOrder{std::make_move_iterator(finishedNodes.rbegin()), std::make_move_iterator(finishedNodes.rend())};

    return topologicalOrder;
}

std::set<NodeIDType> DependencyGraph::getNodeIDsWithNoDependencies() const
{
    std::set<NodeIDType> startingNodeIDs{m_allNodesOrdered.cbegin(), m_allNodesOrdered.cend()};

    // Remove all nodes which have inbound edges
    for (const auto& startNodeId : m_allNodesOrdered)
    {
        for (const auto& neighorId : m_nodeIDToDependentNodeIDs.at(startNodeId))
        {
            startingNodeIDs.erase(neighorId);
        }
    }

    return startingNodeIDs;
}

bool DependencyGraph::isEmpty() const noexcept
{
    return m_allNodesOrdered.empty();
}

void DependencyGraph::removeNode(NodeIDType nodeID)
{
    auto dependentNodeIDs = m_nodeIDToDependentNodeIDs.at(nodeID);
    auto dependencyNodeIDs = m_nodeIDsToDependencyNodeIDs.at(nodeID);

    for (const auto& dependentNodeID : dependentNodeIDs)
    {
        m_nodeIDsToDependencyNodeIDs.at(dependentNodeID).erase(nodeID);
    }

    for (const auto& dependencyNodeID : dependencyNodeIDs)
    {
        m_nodeIDToDependentNodeIDs.at(dependencyNodeID).erase(nodeID);
    }

    m_allNodesOrdered.erase(nodeID);
}

void DependencyGraph::dfsFillOutFinishedNodes(const NodeIDType& startNodeID, std::unordered_set<NodeIDType>& visitedNodes, std::vector<NodeIDType>& finishedNodes) const
{
    visitedNodes.insert(startNodeID);

    for (const auto& neighborID : m_nodeIDToDependentNodeIDs.at(startNodeID))
    {
        if (visitedNodes.find(neighborID) == visitedNodes.end())
        {
            dfsFillOutFinishedNodes(neighborID, visitedNodes, finishedNodes);
        }
    }

    finishedNodes.push_back(startNodeID);
}

}
}
}
