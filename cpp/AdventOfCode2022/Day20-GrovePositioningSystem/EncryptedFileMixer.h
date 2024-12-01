#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day20
{

class EncryptedFileMixer
{
public:
    EncryptedFileMixer(const std::vector<int64_t>& encrypedFile, int64_t decryptionKey);

    void mix(unsigned numMixes);

    int64_t getSumOfGroveCoordinates() const;

private:
    struct Node
    {
        int64_t value;
        Node* next;
        Node* previous;

        Node(int64_t value)
            : value{value}
            , next{nullptr}
            , previous{nullptr}
        {

        }
    };

    using NodeSharedPtr = std::shared_ptr<Node>;

    std::vector<NodeSharedPtr> m_nodes;

    void mixOnce();
    void moveNodeForward(Node* node, int64_t numSteps);
    Node* getNodeAtOffset(Node* node, int offset) const;
    Node* findNodeWithValue(int64_t value) const;
};

}
}
}
