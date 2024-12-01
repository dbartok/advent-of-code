#include "MonkeyParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day21
{

MonkeyParser::MonkeyParser(const std::vector<std::string>& monkeyLines)
{
    for (const auto& monkeyLine : monkeyLines)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, monkeyLine, boost::is_any_of(": "), boost::token_compress_on);

        m_allMonkeyTokens.push_back(std::move(tokens));
    }
}

void MonkeyParser::parse()
{
    createAllNodes();
    setAllChildrenNodes();
    populateHumanPath();
}

MonkeyNodeSharedPtr MonkeyParser::getRootNode() const
{
    return m_monkeyNameToNode.at(ROOT_NODE_NAME);
}

MonkeyNodeSharedPtr MonkeyParser::getHumanNode() const
{
    return m_monkeyNameToNode.at(HUMAN_NODE_NAME);
}

void MonkeyParser::createAllNodes()
{
    for (const auto& monkeyTokens : m_allMonkeyTokens)
    {
        createAndStoreNode(monkeyTokens);
    }
}

void MonkeyParser::setAllChildrenNodes()
{
    for (const auto& monkeyTokens : m_allMonkeyTokens)
    {
        setChildrenNodes(monkeyTokens);
    }
}

void MonkeyParser::populateHumanPath()
{
    MonkeyNode* humanNode = m_monkeyNameToNode.at(HUMAN_NODE_NAME).get();

    for (MonkeyNode* node = humanNode; node != nullptr; node = node->getParentNode())
    {
        node->setIsAncestorOfHumanNode(true);
    }
}

void MonkeyParser::createAndStoreNode(const Tokens& monkeyTokens)
{
    MonkeyNodeSharedPtr node = createNode(monkeyTokens);
    m_monkeyNameToNode.emplace(getName(monkeyTokens), std::move(node));
}

void MonkeyParser::setChildrenNodes(const Tokens& monkeyTokens)
{
    const auto& name = getName(monkeyTokens);

    if (isOperator(monkeyTokens))
    {
        auto& currentNode = m_monkeyNameToNode.at(name);

        const std::string& leftOperandName = monkeyTokens.at(1);
        auto& leftOperandNode = m_monkeyNameToNode.at(leftOperandName);

        const std::string& rightOperandName = monkeyTokens.at(3);
        auto& rightOperandNode = m_monkeyNameToNode.at(rightOperandName);

        currentNode->setOperandNodes(leftOperandNode, rightOperandNode);

        leftOperandNode->setParentNode(currentNode.get());
        rightOperandNode->setParentNode(currentNode.get());
    }
}

MonkeyNodeSharedPtr MonkeyParser::createNode(const Tokens& monkeyTokens)
{
    const auto& name = getName(monkeyTokens);

    if (!isOperator(monkeyTokens))
    {
        return std::make_shared<IntegerNode>(name, std::stoll(monkeyTokens.at(1)));
    }
    else
    {
        const auto& operatorToken = monkeyTokens.at(2).front();
        switch (operatorToken)
        {
            case '+':
                return std::make_shared<AdditionNode>(name);
            case '-':
                return std::make_shared<SubtractionNode>(name);
            case '*':
                return std::make_shared<MultiplicationNode>(name);
            case '/':
                return std::make_shared<DivisionNode>(name);
            default:
                throw std::runtime_error("Invalid operator: " + std::string{operatorToken});
        }
    }
}

const std::string& MonkeyParser::getName(const Tokens& monkeyTokens)
{
    return monkeyTokens.at(0);
}

bool MonkeyParser::isOperator(const Tokens& monkeyTokens)
{
    return monkeyTokens.size() >= 4;
}

}
}
}
