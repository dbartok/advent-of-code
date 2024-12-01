#pragma once

#include "Node.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day18
{

class SnailfishNumberCalculator
{
public:
    void addNumber(Node::SharedPtr addendNode);

    int getMagnitude() const;

private:
    Node::SharedPtr m_rootNode;

    void reduce();
    bool explode();
    bool split();

    static Node::SharedPtr mergeNodes(Node::SharedPtr leftChild, Node::SharedPtr rightChild);
    static Node* findNodeToExplode(Node* rootNode, int nestingLevel);
    static Node* findNodeToSplit(Node* rootNode);
    static Node* findRightmostRegularNode(Node* root);
    static Node* findLeftmostRegularNode(Node* root);
    static void linkNodes(Node* lhsNode, Node* rhsNode);
    static int getMagnitude(Node* root);
};

}
}
}
