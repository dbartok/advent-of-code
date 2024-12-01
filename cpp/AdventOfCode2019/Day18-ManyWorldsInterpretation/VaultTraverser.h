#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>

#include <bitset>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const size_t ALPHABET_LENGTH = 26;
}


namespace AdventOfCode
{
namespace Year2019
{
namespace Day18
{

using VaultMap = std::vector<std::string>;

struct VaultSearchNode
{
    int x;
    int y;
    int numSteps;
    std::bitset<ALPHABET_LENGTH> keys;

    bool operator==(const VaultSearchNode& other) const
    {
        return x == other.x && y == other.y && keys == other.keys;
    }
};

class VaultTraverser
{
public:
    VaultTraverser(VaultMap vaultMap);

    void traverseAllKeys();

    int getShortestPathLength() const;

private:
    VaultMap m_map;
    std::unordered_set<char> m_allAvailableKeys;

    int m_shortestPathLength = std::numeric_limits<int>::max();

    VaultSearchNode createInitialNode();

    std::vector<VaultSearchNode> createNeighborNodes(const VaultSearchNode& currentNode) const;
    std::vector<VaultSearchNode> createSpatialNeighborNodes(const VaultSearchNode& currentNode) const;
    bool isKey(char tile) const;
    bool isObstructed(char tile, const std::bitset<ALPHABET_LENGTH>& keys) const;
    bool isDoor(char tile) const;
    char getKeyForDoor(char door) const;
};

}
}
}
