#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>
#include <boost/optional.hpp>

#include <set>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day17
{

using Coordinates = std::pair<int, int>;

struct Node
{
    Coordinates position;
    Coordinates arrivalDirection;
    int numTilesMovedInDirection;

    mutable int pathCost;

    bool operator==(const Node& other) const
    {
        return this->position == other.position
            && this->arrivalDirection == other.arrivalDirection
            && this->numTilesMovedInDirection == other.numTilesMovedInDirection;
    }
};

struct NodeHash
{
    size_t operator()(const Node& node) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, node.position);
        boost::hash_combine(seed, node.arrivalDirection);
        boost::hash_combine(seed, node.numTilesMovedInDirection);

        return seed;
    }
};

struct NodePtrCostCmp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        if (lhs->pathCost < rhs->pathCost)
        {
            return true;
        }

        if (lhs->pathCost > rhs->pathCost)
        {
            return false;
        }

        return lhs < rhs;
    }
};


class CityBlockTraverser
{
public:
    CityBlockTraverser(std::vector<std::vector<int>> map, int minNumMovesInSingleDirection, int maxNumMovesInSingleDirection);

    void traverse();

    int getMinHeatLoss() const;

private:
    std::vector<std::vector<int>> m_map;
    size_t m_width;
    size_t m_height;
    int m_minNumMovesInSingleDirection;
    int m_maxNumMovesInSingleDirection;

    int m_minHeatLoss = std::numeric_limits<int>::max();

    std::unordered_set<Node, NodeHash> m_allNodes;
    std::set<const Node*, NodePtrCostCmp> m_activeNodes;

    std::vector<Node> getAllNeighborNodes(const Node& baseNode) const;
    boost::optional<Node> getNodeInDirection(const Node& baseNode, const Coordinates& direction, int newNumTilesMovedInDirection) const;
    int getCostAt(const Coordinates& coordinates) const;
};

}
}
}
