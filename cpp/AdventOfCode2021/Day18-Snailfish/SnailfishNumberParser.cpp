#include "SnailfishNumberParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day18
{

SnailfishNumberParser::SnailfishNumberParser(std::string snailfishNumberString)
    : m_snailfishNumberString{std::move(snailfishNumberString)}
{
    m_snailfishNumberString.erase(std::remove(m_snailfishNumberString.begin(), m_snailfishNumberString.end(), ','), m_snailfishNumberString.end());
}

Node::SharedPtr SnailfishNumberParser::createRootNode()
{
    Node::SharedPtr rootNode = std::make_shared<Node>();

    const char c = getNextChar();
    if (c == '[')
    {
        rootNode->leftChild = createRootNode();
        rootNode->rightChild = createRootNode();
        if (getNextChar() != ']')
        {
            throw std::runtime_error("Missing closing bracket");
        }
    }
    else
    {
        rootNode->number = c - '0';
        chainWithPrevCreatedNode(rootNode.get());
    }

    return rootNode;
}

char SnailfishNumberParser::getNextChar()
{
    return m_snailfishNumberString.at(m_index++);
}

void SnailfishNumberParser::chainWithPrevCreatedNode(Node* node)
{
    if (m_prevCreatedNode)
    {
        m_prevCreatedNode->nextNode = node;
    }
    node->prevNode = m_prevCreatedNode;
    m_prevCreatedNode = node;
}

}
}
}
