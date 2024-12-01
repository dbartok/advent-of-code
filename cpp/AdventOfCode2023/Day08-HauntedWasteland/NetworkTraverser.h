#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day08
{

using NodeID = std::string;

struct Junction
{
    NodeID left;
    NodeID right;
};

using NodeIDToJunction = std::unordered_map<NodeID, Junction>;

class NetworkTraverser
{
public:
    NetworkTraverser(std::string instructions, NodeIDToJunction nodeIDToJunction, NodeID startNodeID, std::string endNodeIDRegex);

    void traverse();

    int getNumSteps() const;

private:
    const std::string m_instructions;
    const NodeIDToJunction m_nodeIDToJunction;
    const std::string m_endNodeIDRegex;

    NodeID m_currentNodeID;
    int m_numSteps = 0;

    void executeSingleInstruction();

    bool isAtEndpoint() const;
};

}
}
}
