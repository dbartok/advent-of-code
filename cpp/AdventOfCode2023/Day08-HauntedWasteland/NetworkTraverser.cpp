#include "NetworkTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day08
{

NetworkTraverser::NetworkTraverser(std::string instructions, NodeIDToJunction nodeIDToJunction, NodeID startNodeID, std::string endNodeIDRegex)
    : m_instructions{std::move(instructions)}
    , m_nodeIDToJunction{std::move(nodeIDToJunction)}
    , m_currentNodeID{std::move(startNodeID)}
    , m_endNodeIDRegex{std::move(endNodeIDRegex)}
{

}

void NetworkTraverser::traverse()
{
    while (!isAtEndpoint())
    {
        executeSingleInstruction();
    }
}

int NetworkTraverser::getNumSteps() const
{
    return m_numSteps;
}

void NetworkTraverser::executeSingleInstruction()
{
    const char currentInstruction = m_instructions.at(m_numSteps % m_instructions.size());
    const Junction& currentJunction = m_nodeIDToJunction.at(m_currentNodeID);

    if (currentInstruction == 'L')
    {
        m_currentNodeID = currentJunction.left;
    }
    else if (currentInstruction == 'R')
    {
        m_currentNodeID = currentJunction.right;
    }

    ++m_numSteps;
}

bool NetworkTraverser::isAtEndpoint() const
{
    return std::regex_match(m_currentNodeID, std::regex{m_endNodeIDRegex});
}

}
}
}
