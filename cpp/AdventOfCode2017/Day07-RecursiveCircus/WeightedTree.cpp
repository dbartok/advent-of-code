#include "WeightedTree.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
#include <unordered_set>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day07
{

WeightedTree::TreeNode::TreeNode(std::string name, int weight) noexcept
    : name{std::move(name)}
    , weight{weight}
    , childrenSharedPtrs{}
    , parentWeakPtr{}
    , totalSubtreeWeight{0}
{

}

int WeightedTree::TreeNode::totalSiblingCount() const
{
    // Root node
    if (!parentWeakPtr.is_initialized())
    {
        return 1;
    }

    auto parentStrongPtr = parentWeakPtr.get().lock();
    if (!parentStrongPtr)
    {
        throw("Memory management error - parent node is already destroyed.");
    }

    return parentStrongPtr->childrenSharedPtrs.size();
}

WeightedTree::WeightedTree(TreeNodeSharedPtr root)
    : m_root{std::move(root)}
{
    recalculateSubtreeWeightsForNode(*m_root);
}

int WeightedTree::getCorrectWeightForSingleWrongWeight() const
{
    if (m_root == nullptr)
    {
        throw std::runtime_error("Tree is empty.");
    }

    return traverseForCorrectWeightFromNode(*m_root, 0);
}

WeightedTree WeightedTree::fromNodeDescriptors(const std::vector<NodeDescriptor>& nodeDescriptors)
{
    std::unordered_map<std::string, TreeNodeSharedPtr> allNodes;

    // Create all nodes
    for (const auto& nodeDescriptor : nodeDescriptors)
    {
        TreeNodeSharedPtr newNodeSharedPtr = std::make_shared<TreeNode>(nodeDescriptor.name, nodeDescriptor.weight);

        bool insertionTookPlace;
        std::tie(std::ignore, insertionTookPlace) = allNodes.insert(std::make_pair(nodeDescriptor.name, std::move(newNodeSharedPtr)));

        if (!insertionTookPlace)
        {
            throw std::runtime_error("Node with duplicate name encountered.");
        }
    }

    // Used to determine the root
    std::unordered_map<std::string, TreeNodeSharedPtr> allNodesWithoutParents = allNodes;

    // Set children
    for (const auto& nodeDescriptor : nodeDescriptors)
    {
        const std::string& name = nodeDescriptor.name;
        const TreeNodeSharedPtr& nodeSharedPtr = allNodes.at(name);

        for (const auto& childName : nodeDescriptor.childrenNames)
        {
            const TreeNodeSharedPtr& childSharedPtr = allNodes.at(childName);
            nodeSharedPtr->childrenSharedPtrs.push_back(childSharedPtr);
            childSharedPtr->parentWeakPtr = nodeSharedPtr;

            allNodesWithoutParents.erase(childName);
        }
    }

    if (allNodesWithoutParents.size() != 1)
    {
        throw std::runtime_error("There are either zero or more than one tree roots.");
    }

    TreeNodeSharedPtr root = allNodesWithoutParents.cbegin()->second;
    return WeightedTree{std::move(root)};
}

void WeightedTree::recalculateSubtreeWeightsForNode(TreeNode& node)
{
    for (const auto& childSharedPtr : node.childrenSharedPtrs)
    {
        recalculateSubtreeWeightsForNode(*childSharedPtr);
    }

    node.totalSubtreeWeight = std::accumulate(node.childrenSharedPtrs.cbegin(), node.childrenSharedPtrs.cend(), node.weight,
                                                        [](int sum, const TreeNodeSharedPtr& childSharedPtr) noexcept
                                                        {
                                                            return sum + childSharedPtr->totalSubtreeWeight;
                                                        });
}

int WeightedTree::traverseForCorrectWeightFromNode(const TreeNode& currentNode, int weightSurplus) const
{
    const std::vector<TreeNodeSharedPtr>& childrenSharedPtrs = currentNode.childrenSharedPtrs;
    bool balancedSoFar = (weightSurplus == 0);

    // Exactly one child, skip forward
    if (childrenSharedPtrs.size() == 1)
    {
        return traverseForCorrectWeightFromNode(*childrenSharedPtrs.front(), weightSurplus);
    }

    bool areAllChildrenEqualSubtreeWeight = Utils::allElementsEqual(childrenSharedPtrs.cbegin(), childrenSharedPtrs.cend(),
                                                                    [](const TreeNodeSharedPtr& lhs, const TreeNodeSharedPtr& rhs) noexcept
                                                                    {
                                                                        return lhs->totalSubtreeWeight == rhs->totalSubtreeWeight;
                                                                    });


    // Children are balanced, meaning there are no further imbalances down the tree
    if (areAllChildrenEqualSubtreeWeight)
    {
        // There weren't any imbalances to begin with, so there is no weight to correct at all
        if (weightSurplus == 0)
        {
            throw std::runtime_error("Tree is already balanced.");
        }

        // If the wrong node is an only child, changing its weight is equivalent to changing the weight of its parent
        if (currentNode.totalSiblingCount() == 1)
        {
            throw std::runtime_error("The wrong weight is ambiguous - it could both be a node and its parent.");
        }

        // This is the node that has to be balanced, return the correct weight for it
        return currentNode.weight - weightSurplus;
    }

    // Two imbalanced children
    // In this case, the tree can always be balanced by changing one weight in either subtree
    if (childrenSharedPtrs.size() == 2)
    {
        throw std::runtime_error("The wrong weight is ambiguous - it could be both in both subtrees of a node.");
    }

    // Three or more children with an imbalance somewhere
    if (childrenSharedPtrs.size() >= 3)
    {
        // Determine child with the unique subtree weight, because that's the direction where the imbalance is
        // We also need the value of the non-unique subtree weight so that we know the weight difference
        std::unordered_map<int, TreeNodeSharedPtr> nodeSharedPtrToSubtreeWeightMap; // OrderedNodeIDs with potentially unique subtree weight
        std::unordered_set<int> uniqueWeightSet;
        int nonUniqueSubtreeWeight = -1;

        for (const auto& childSharedPtr : childrenSharedPtrs)
        {
            bool insertionTookPlace;
            std::tie(std::ignore, insertionTookPlace) = uniqueWeightSet.insert(childSharedPtr->totalSubtreeWeight);

            // This child doesn't have a unique subtree weight
            if (!insertionTookPlace)
            {
                nonUniqueSubtreeWeight = childSharedPtr->totalSubtreeWeight;
                nodeSharedPtrToSubtreeWeightMap.erase(childSharedPtr->totalSubtreeWeight);
            }
            else
            {
                nodeSharedPtrToSubtreeWeightMap.insert(std::make_pair(childSharedPtr->totalSubtreeWeight, childSharedPtr));
            }
        }

        // Only the child with the unique subtere weight remains in the map at this point
        if (nodeSharedPtrToSubtreeWeightMap.size() != 1)
        {
            throw std::runtime_error("Unable to balance by changing only one weight - no single unique value for subtree weight found among children.");
        }

        assert(nonUniqueSubtreeWeight != -1);

        TreeNodeSharedPtr uniqueWeightNodeSharedPtr = nodeSharedPtrToSubtreeWeightMap.cbegin()->second;
        int imbalancedChildWeightExtra = uniqueWeightNodeSharedPtr->totalSubtreeWeight - nonUniqueSubtreeWeight;

        if (weightSurplus != 0 && imbalancedChildWeightExtra != weightSurplus)
        {
            throw std::runtime_error("Unable to balance by changing only one weight - two different weight surpluses encountered.");
        }

        // Traverse in the only direction where the imbalance can be corrected
        return traverseForCorrectWeightFromNode(*uniqueWeightNodeSharedPtr, imbalancedChildWeightExtra);
    }
}

}
}
}
