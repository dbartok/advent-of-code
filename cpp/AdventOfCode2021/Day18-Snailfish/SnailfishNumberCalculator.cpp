#include "SnailfishNumberCalculator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
#include <cmath>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

int EXPLODE_NESTING_LEVEL_THRESHOLD = 4;
int SPLIT_THRESHOLD = 10;
int MAGNITUDE_LEFT_MULTIPLIER = 3;
int MAGNITUDE_RIGHT_MULTIPLIER = 2;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day18
{

void SnailfishNumberCalculator::addNumber(Node::SharedPtr addendNode)
{
    if (!m_rootNode)
    {
        m_rootNode = addendNode;
    }
    else
    {
        m_rootNode = mergeNodes(m_rootNode, addendNode);
        reduce();
    }
}

int SnailfishNumberCalculator::getMagnitude() const
{
    return getMagnitude(m_rootNode.get());
}

void SnailfishNumberCalculator::reduce()
{
    while (true)
    {
        if (explode())
        {
            continue;
        }

        if (split())
        {
            continue;
        }

        break;
    }
}

bool SnailfishNumberCalculator::explode()
{
    Node* nodeToExplode = findNodeToExplode(m_rootNode.get(), 0);

    if (!nodeToExplode)
    {
        return false;
    }

    auto leftChild = nodeToExplode->leftChild;
    if (Node* prevNode = leftChild->prevNode)
    {
        prevNode->number.value() += leftChild->number.value();
        linkNodes(prevNode, nodeToExplode);
    }

    auto rightChild = nodeToExplode->rightChild;
    if (Node* nextNode = rightChild->nextNode)
    {
        nextNode->number.value() += rightChild->number.value();
        linkNodes(nodeToExplode, nextNode);
    }

    nodeToExplode->leftChild = nullptr;
    nodeToExplode->rightChild = nullptr;
    nodeToExplode->number = 0;

    return true;
}

bool SnailfishNumberCalculator::split()
{
    Node* nodeToSplit = findNodeToSplit(m_rootNode.get());

    if (!nodeToSplit)
    {
        return false;
    }

    Node::SharedPtr newLeftChild = std::make_shared<Node>();
    newLeftChild->number = nodeToSplit->number.value() / 2;
    if (Node* prevNode = nodeToSplit->prevNode)
    {
        linkNodes(prevNode, newLeftChild.get());
    }

    Node::SharedPtr newRightChild = std::make_shared<Node>();
    newRightChild->number = (nodeToSplit->number.value() + 1) / 2;
    if (Node* nextNode = nodeToSplit->nextNode)
    {
        linkNodes(newRightChild.get(), nextNode);
    }

    linkNodes(newLeftChild.get(), newRightChild.get());

    nodeToSplit->leftChild = newLeftChild;
    nodeToSplit->rightChild = newRightChild;
    nodeToSplit->number.reset();

    return true;
}

Node::SharedPtr SnailfishNumberCalculator::mergeNodes(Node::SharedPtr leftChild, Node::SharedPtr rightChild)
{
    Node::SharedPtr newRootNode = std::make_shared<Node>();

    newRootNode->leftChild = leftChild;
    newRootNode->rightChild = rightChild;

    Node* rightmostRegularNodeInLeftSubtree = findRightmostRegularNode(leftChild.get());
    Node* leftmostRegularNodeInRightSubtree = findLeftmostRegularNode(rightChild.get());

    rightmostRegularNodeInLeftSubtree->nextNode = leftmostRegularNodeInRightSubtree;
    leftmostRegularNodeInRightSubtree->prevNode = rightmostRegularNodeInLeftSubtree;

    return newRootNode;
}

Node* SnailfishNumberCalculator::findNodeToExplode(Node* rootNode, int nestingLevel)
{
    if (!(rootNode->leftChild && rootNode->rightChild))
    {
        return nullptr;
    }

    const bool areBothChildrenRegularNodes = rootNode->leftChild->number && rootNode->rightChild->number;

    if (areBothChildrenRegularNodes && nestingLevel >= EXPLODE_NESTING_LEVEL_THRESHOLD)
    {
        return rootNode;
    }

    if (Node* node = findNodeToExplode(rootNode->leftChild.get(), nestingLevel + 1))
    {
        return node;
    }

    return findNodeToExplode(rootNode->rightChild.get(), nestingLevel + 1);
}

Node* SnailfishNumberCalculator::findNodeToSplit(Node* rootNode)
{
    if (!rootNode)
    {
        return nullptr;
    }

    if (rootNode->number.value_or(0) >= SPLIT_THRESHOLD)
    {
        return rootNode;
    }

    if (Node* node = findNodeToSplit(rootNode->leftChild.get()))
    {
        return node;
    }

    return findNodeToSplit(rootNode->rightChild.get());
}

Node* SnailfishNumberCalculator::findRightmostRegularNode(Node* root)
{
    if (root->number)
    {
        return root;
    }

    return findRightmostRegularNode(root->rightChild.get());
}

Node* SnailfishNumberCalculator::findLeftmostRegularNode(Node* root)
{
    if (root->number)
    {
        return root;
    }

    return findLeftmostRegularNode(root->leftChild.get());
}

void SnailfishNumberCalculator::linkNodes(Node* lhsNode, Node* rhsNode)
{
    lhsNode->nextNode = rhsNode;
    rhsNode->prevNode = lhsNode;
}

int SnailfishNumberCalculator::getMagnitude(Node* root)
{
    if (root->number)
    {
        return root->number.value();
    }

    return MAGNITUDE_LEFT_MULTIPLIER * getMagnitude(root->leftChild.get()) + MAGNITUDE_RIGHT_MULTIPLIER * getMagnitude(root->rightChild.get());
}

}
}
}
