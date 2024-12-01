#include "Day24-ElectromagneticMoat.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

#include "BridgeGraph.h"

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day24
{

namespace
{

const size_t MAX_NODES = 51;

}

BridgeGraph::NodeIDToNeighbors nodeIDToNeighborsFromComponentLines(const std::vector<std::string>& componentLines)
{
    BridgeGraph::NodeIDToNeighbors nodeIDToNeighbors(MAX_NODES);
    for (const auto& line : componentLines)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_any_of("/"));
        if (tokens.size() != 2)
        {
            throw std::runtime_error("Expected exactly two tokens.");
        }

        const BridgeGraph::NodeIDType node1 = boost::lexical_cast<BridgeGraph::NodeIDType>(tokens[0]);
        const BridgeGraph::NodeIDType node2 = boost::lexical_cast<BridgeGraph::NodeIDType>(tokens[1]);

        if (node1 >= MAX_NODES || node2 >= MAX_NODES)
        {
            throw std::runtime_error("Node ID is too large.");
        }

        nodeIDToNeighbors[node1].push_back(node2);
        nodeIDToNeighbors[node2].push_back(node1);
    }

    return nodeIDToNeighbors;
}

unsigned strengthOfStrongestBridge(const std::vector<std::string>& componentLines)
{
    BridgeGraph::NodeIDToNeighbors nodeIDToNeighbors = nodeIDToNeighborsFromComponentLines(componentLines);
    BridgeGraph bridgeGraph{nodeIDToNeighbors};
    return bridgeGraph.maxCostWalk();
}

unsigned strengthOfStrongestLongestBridge(const std::vector<std::string>& componentLines)
{
    BridgeGraph::NodeIDToNeighbors nodeIDToNeighbors = nodeIDToNeighborsFromComponentLines(componentLines);
    BridgeGraph bridgeGraph{nodeIDToNeighbors};
    return bridgeGraph.maxCostLongestWalk();
}

}
}
}
