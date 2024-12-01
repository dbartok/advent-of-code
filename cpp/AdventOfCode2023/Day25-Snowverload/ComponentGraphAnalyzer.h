#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS

#include <memory>
#include <unordered_map>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day25
{

struct Edge;
using EdgePtrs = std::vector<Edge*>;
using EdgeSharedPtr = std::shared_ptr<Edge>;
using EdgeSharedPtrs = std::vector<EdgeSharedPtr>;
using NodeNameToEdgeSharedPtrs = std::unordered_map<std::string, EdgeSharedPtrs>;

struct Edge
{
    std::string sourceNodeName;
    std::string destinationNodeName;
    int capacity = 1;
    int flow = 0;
    Edge* reverse = nullptr;

    Edge(std::string sourceNodeName, std::string destinationNodeName)
        : sourceNodeName{std::move(sourceNodeName)}
        , destinationNodeName{std::move(destinationNodeName)}
    {

    }

    bool hasFreeCapacity() const
    {
        return capacity - flow > 0;
    }
};

class ComponentGraphAnalyzer
{
public:
    ComponentGraphAnalyzer(NodeNameToEdgeSharedPtrs nodeNameToEdgeSharedPtrs, std::string startNodeName, std::string endNodeName);

    void determineMaxFlow();

    int getMaxFlowValue() const;
    int getMinCutPartitionSizesProduct() const;

private:
    struct TraversalNode
    {
        std::string name;
        EdgePtrs path;

        TraversalNode(std::string name, EdgePtrs path)
            : name{std::move(name)}
            , path{std::move(path)}
        {

        }
    };

    NodeNameToEdgeSharedPtrs m_nodeNameToEdgeSharedPtrs;
    std::string m_startNodeName;
    std::string m_endNodeName;

    std::unordered_set<std::string> m_visitedNodeNames;
    int m_maxFlowValue = 0;

    EdgePtrs createAugmentingPath();
    void processAugmentingPath(const EdgePtrs& augmentingPath);
};

}
}
}
