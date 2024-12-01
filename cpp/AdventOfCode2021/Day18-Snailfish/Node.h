#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day18
{

struct Node
{
    using SharedPtr = std::shared_ptr<Node>;

    Node::SharedPtr leftChild = nullptr;
    Node::SharedPtr rightChild = nullptr;
    boost::optional<int> number;

    // These link the node to the prev/next regular node in the inorder traversal
    Node* prevNode = nullptr;
    Node* nextNode = nullptr;
};

}
}
}
