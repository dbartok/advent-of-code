#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_set>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day06
{

using NodeIDType = std::string;
using NodeIDs = std::vector<NodeIDType>;

enum class EdgeType
{
    DIRECTED,
    UNDIRECTED,
};

class OrbitMap
{
public:
    void addEdge(NodeIDType from, NodeIDType to, EdgeType edgeType);

    unsigned getNumTransitiveOrbits() const;
    unsigned getDistanceBetweenStartAndGoal() const;

private:
    const NodeIDType CENTER_OF_MASS = "COM";
    const NodeIDType START = "YOU";
    const NodeIDType GOAL = "SAN";

    struct NodeIDAndDistance
    {
        NodeIDType nodeID;
        unsigned distance;
    };

    std::unordered_map<NodeIDType, NodeIDs> m_nodeIDToAdjacentNodeIDs;

    unsigned getNumTransitiveOrbitsRecursive(const NodeIDType& startNodeID, unsigned numAncestors) const;
};

}
}
}
