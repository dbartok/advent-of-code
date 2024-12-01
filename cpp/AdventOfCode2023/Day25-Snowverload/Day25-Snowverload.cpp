#include "Day25-Snowverload.h"

#include "ComponentGraphAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int GRAPH_EDGE_CONNECTIVITY = 3;

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day25
{

NodeNameToEdgeSharedPtrs parseConnectionLines(const std::vector<std::string>& connectionLines)
{
    NodeNameToEdgeSharedPtrs nodeNameToEdgeSharedPtrs;

    for (const auto& line : connectionLines)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_any_of(": "), boost::token_compress_on);

        const std::string& sourceNodeName = tokens.front();

        for (auto destinationNodeNameIter = tokens.cbegin() + 1; destinationNodeNameIter != tokens.cend(); ++destinationNodeNameIter)
        {
            const std::string& destinationNodeName = *destinationNodeNameIter;

            EdgeSharedPtr forwardsEdgeSharedPtr = std::make_shared<Edge>(sourceNodeName, destinationNodeName);
            EdgeSharedPtr backwardsEdgeSharedPtr = std::make_shared<Edge>(destinationNodeName, sourceNodeName);

            forwardsEdgeSharedPtr->reverse = backwardsEdgeSharedPtr.get();
            backwardsEdgeSharedPtr->reverse = forwardsEdgeSharedPtr.get();

            nodeNameToEdgeSharedPtrs[sourceNodeName].push_back(std::move(forwardsEdgeSharedPtr));
            nodeNameToEdgeSharedPtrs[destinationNodeName].push_back(std::move(backwardsEdgeSharedPtr));
        }
    }

    return nodeNameToEdgeSharedPtrs;
}

int componentSizesAfterCutsMultipliedTogether(const std::vector<std::string>& connectionLines)
{
    NodeNameToEdgeSharedPtrs nodeNameToEdgeSharedPtrs = parseConnectionLines(connectionLines);
    const std::string& startNodeName = nodeNameToEdgeSharedPtrs.cbegin()->first;

    for (auto endNodeNameAndEdgePtrsIter = std::next(nodeNameToEdgeSharedPtrs.cbegin()); endNodeNameAndEdgePtrsIter != nodeNameToEdgeSharedPtrs.cend(); ++endNodeNameAndEdgePtrsIter)
    {
        const std::string& endNodeName = endNodeNameAndEdgePtrsIter->first;

        ComponentGraphAnalyzer componentGraphAnalyzer{nodeNameToEdgeSharedPtrs, startNodeName, endNodeName};
        componentGraphAnalyzer.determineMaxFlow();

        if (componentGraphAnalyzer.getMaxFlowValue() == GRAPH_EDGE_CONNECTIVITY)
        {
            return componentGraphAnalyzer.getMinCutPartitionSizesProduct();
        }
    }

    throw std::runtime_error("No solution found.");
}

}
}
}