#include "EncryptedFileMixer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const std::vector<int> GROVE_OFFSETS{1000, 2000, 3000};

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day20
{

EncryptedFileMixer::EncryptedFileMixer(const std::vector<int64_t>& encrypedFile, int64_t decryptionKey)
{
    Node* previousNode = nullptr;
    for (int64_t value : encrypedFile)
    {
        m_nodes.push_back(std::make_shared<Node>(value * decryptionKey));
        Node* currentNode = m_nodes.back().get();

        if (previousNode)
        {
            previousNode->next = currentNode;
            currentNode->previous = previousNode;
        }

        previousNode = currentNode;
    }

    // Link last node and first node
    m_nodes.back()->next = m_nodes.front().get();
    m_nodes.front()->previous = m_nodes.back().get();
}

void EncryptedFileMixer::mix(unsigned numMixes)
{
    for (unsigned i = 0; i < numMixes; ++i)
    {
        mixOnce();
    }
}

int64_t EncryptedFileMixer::getSumOfGroveCoordinates() const
{
    Node* baseNode = findNodeWithValue(0);

    int64_t sumOfGroveCoordinates = 0;

    for (const int groveOffset : GROVE_OFFSETS)
    {
        const Node* groveCoordinateNode = getNodeAtOffset(baseNode, groveOffset);
        sumOfGroveCoordinates += groveCoordinateNode->value;
    }

    return sumOfGroveCoordinates;
}

void EncryptedFileMixer::mixOnce()
{
    for (auto& node : m_nodes)
    {
        moveNodeForward(node.get(), node->value);
    }
}

void EncryptedFileMixer::moveNodeForward(Node* node, int64_t numSteps)
{
    // Unlink node
    node->previous->next = node->next;
    node->next->previous = node->previous;

    // Simplify the number of steps
    const int modulus = m_nodes.size() - 1;
    numSteps %= modulus;
    if (numSteps < 0)
    {
        numSteps += modulus;
    }

    // Find new previous node
    Node* newPreviousNode = node->previous;
    for (size_t i = 0; i < numSteps; ++i)
    {
        newPreviousNode = newPreviousNode->next;
    }

    // Link with new neighbors
    auto newNextNode = newPreviousNode->next;
    newPreviousNode->next = node;
    node->previous = newPreviousNode;
    newNextNode->previous = node;
    node->next = newNextNode;
}

EncryptedFileMixer::Node* EncryptedFileMixer::getNodeAtOffset(Node* node, int offset) const
{
    offset %= m_nodes.size();
    Node* offsetNode = node;
    for (size_t i = 0; i < offset; ++i)
    {
        offsetNode = offsetNode->next;
    }

    return offsetNode;
}

EncryptedFileMixer::Node* EncryptedFileMixer::findNodeWithValue(int64_t value) const
{
    Node* node = m_nodes.at(0).get();

    while (node->value != value)
    {
        node = node->next;
    }

    return node;
}

}
}
}
