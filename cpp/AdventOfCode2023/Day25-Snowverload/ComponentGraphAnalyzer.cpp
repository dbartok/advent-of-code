#include "ComponentGraphAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day25
{

ComponentGraphAnalyzer::ComponentGraphAnalyzer(NodeNameToEdgeSharedPtrs nodeNameToEdgeSharedPtrs, std::string startNodeName, std::string endNodeName)
    : m_nodeNameToEdgeSharedPtrs{std::move(nodeNameToEdgeSharedPtrs)}
    , m_startNodeName{std::move(startNodeName)}
    , m_endNodeName{std::move(endNodeName)}
{

}

void ComponentGraphAnalyzer::determineMaxFlow()
{
    int maxFlowValue = 0;

    while (true)
    {
        EdgePtrs augmentingPath = createAugmentingPath();
        if (augmentingPath.empty())
        {
            break;
        }

        processAugmentingPath(augmentingPath);

        ++maxFlowValue;
    }

    m_maxFlowValue = maxFlowValue;
}

int ComponentGraphAnalyzer::getMaxFlowValue() const
{
    return m_maxFlowValue;
}

int ComponentGraphAnalyzer::getMinCutPartitionSizesProduct() const
{
    return m_visitedNodeNames.size() * (m_nodeNameToEdgeSharedPtrs.size() - m_visitedNodeNames.size());
}

EdgePtrs ComponentGraphAnalyzer::createAugmentingPath()
{
    std::queue<TraversalNode> queue;
    queue.emplace(m_startNodeName, EdgePtrs{});

    m_visitedNodeNames.clear();
    m_visitedNodeNames.insert(m_startNodeName);

    while (!queue.empty())
    {
        TraversalNode currentTraversalNode = queue.front();
        queue.pop();

        if (currentTraversalNode.name == m_endNodeName)
        {
            return currentTraversalNode.path;
        }

        const EdgeSharedPtrs& neighborEdgeSharedPtrs = m_nodeNameToEdgeSharedPtrs.at(currentTraversalNode.name);

        for (const EdgeSharedPtr& neighborEdgeSharedPtr : neighborEdgeSharedPtrs)
        {
            if (neighborEdgeSharedPtr->hasFreeCapacity() && m_visitedNodeNames.insert(neighborEdgeSharedPtr->destinationNodeName).second)
            {
                EdgePtrs newPath{currentTraversalNode.path};
                newPath.push_back(neighborEdgeSharedPtr.get());
                queue.emplace(neighborEdgeSharedPtr->destinationNodeName, std::move(newPath));
            }
        }
    }

    return {};
}

void ComponentGraphAnalyzer::processAugmentingPath(const EdgePtrs& augmentingPath)
{
    for (Edge* edgePtr : augmentingPath)
    {
        edgePtr->flow += 1;
        edgePtr->reverse->flow -= 1;
    }
}

}
}
}
