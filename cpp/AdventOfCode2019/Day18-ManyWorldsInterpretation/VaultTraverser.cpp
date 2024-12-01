#include "VaultTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day18
{

struct VaultSearchNodeHash
{
    std::size_t operator()(const VaultSearchNode& node) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, node.x);
        boost::hash_combine(seed, node.y);
        boost::hash_combine(seed, node.keys.to_ulong());

        return seed;
    }
};

VaultTraverser::VaultTraverser(VaultMap vaultMap)
    : m_map{std::move(vaultMap)}
{
    for (int j = 0; j < m_map.size(); ++j)
    {
        for (int i = 0; i < m_map.at(j).size(); ++i)
        {
            char tile = m_map.at(j).at(i);
            if (isKey(tile))
            {
                m_allAvailableKeys.insert(tile);
            }
        }
    }
}

void VaultTraverser::traverseAllKeys()
{
    std::queue<VaultSearchNode> bfsQueue;
    VaultSearchNode initialNode = createInitialNode();
    bfsQueue.push(initialNode);

    std::unordered_set<VaultSearchNode, VaultSearchNodeHash> visited;
    visited.insert(initialNode);

    while (!bfsQueue.empty())
    {
        VaultSearchNode currentNode = bfsQueue.front();
        bfsQueue.pop();

        if (currentNode.keys.count() == m_allAvailableKeys.size())
        {
            m_shortestPathLength = currentNode.numSteps;
            return;
        }

        std::vector<VaultSearchNode> neighborNodes = createNeighborNodes(currentNode);

        for (auto& node : neighborNodes)
        {
            if (visited.find(node) == visited.cend())
            {
                visited.insert(node);
                bfsQueue.push(node);
            }
        }
    }

    throw std::runtime_error("Unable to find all keys.");
}

int VaultTraverser::getShortestPathLength() const
{
    return m_shortestPathLength;
}

VaultSearchNode VaultTraverser::createInitialNode()
{
    for (int j = 0; j < m_map.size(); ++j)
    {
        for (int i = 0; i < m_map.at(j).size(); ++i)
        {
            if (m_map.at(j).at(i) == '@')
            {
                m_map.at(j).at(i) = '.';
                return VaultSearchNode{i, j, 0, {}};
            }
        }
    }

    throw std::runtime_error("Unable to create initial state.");
}

std::vector<VaultSearchNode> VaultTraverser::createNeighborNodes(const VaultSearchNode& currentNode) const
{
    std::vector<VaultSearchNode> neighborNodes;
    std::vector<VaultSearchNode> spatialNeighborNodes = createSpatialNeighborNodes(currentNode);

    for (auto& spatialNeighborNode : spatialNeighborNodes)
    {
        char tile = m_map.at(spatialNeighborNode.y).at(spatialNeighborNode.x);
        if (isKey(tile))
        {
            spatialNeighborNode.keys.set(tile - 'a');
        }

        if (!isObstructed(tile, spatialNeighborNode.keys))
        {
            neighborNodes.push_back(spatialNeighborNode);
        }
    }

    return neighborNodes;
}

std::vector<VaultSearchNode> VaultTraverser::createSpatialNeighborNodes(const VaultSearchNode& currentNode) const
{
    std::vector<VaultSearchNode> spatialNeighborNodes;
    spatialNeighborNodes.push_back(VaultSearchNode{currentNode.x + 1, currentNode.y, currentNode.numSteps + 1, currentNode.keys});
    spatialNeighborNodes.push_back(VaultSearchNode{currentNode.x - 1, currentNode.y, currentNode.numSteps + 1, currentNode.keys});
    spatialNeighborNodes.push_back(VaultSearchNode{currentNode.x, currentNode.y + 1, currentNode.numSteps + 1, currentNode.keys});
    spatialNeighborNodes.push_back(VaultSearchNode{currentNode.x, currentNode.y - 1, currentNode.numSteps + 1, currentNode.keys});
    return spatialNeighborNodes;
}

bool VaultTraverser::isKey(char tile) const
{
    return tile >= 'a' && tile <= 'z';
}

bool VaultTraverser::isObstructed(char tile, const std::bitset<ALPHABET_LENGTH>& keys) const
{
    if (tile == '#')
    {
        return true;
    }

    if (isDoor(tile))
    {
        char key = getKeyForDoor(tile);
        if (m_allAvailableKeys.find(key) != m_allAvailableKeys.cend() && !keys.test(key - 'a'))
        {
            return true;
        }
    }

    return false;
}

bool VaultTraverser::isDoor(char tile) const
{
    return tile >= 'A' && tile <= 'Z';
}

char VaultTraverser::getKeyForDoor(char door) const
{
    return std::tolower(door);
}

}
}
}
