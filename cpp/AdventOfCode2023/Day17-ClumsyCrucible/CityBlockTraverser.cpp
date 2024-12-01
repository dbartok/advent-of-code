#include "CityBlockTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day17
{

CityBlockTraverser::CityBlockTraverser(std::vector<std::vector<int>> map, int minNumMovesInSingleDirection, int maxNumMovesInSingleDirection)
    : m_map{std::move(map)}
    , m_width{m_map.front().size()}
    , m_height{m_map.size()}
    , m_minNumMovesInSingleDirection{minNumMovesInSingleDirection}
    , m_maxNumMovesInSingleDirection{maxNumMovesInSingleDirection}
{

}

void CityBlockTraverser::traverse()
{
    Node startNode{{0, 0}, {1, 0}, 0, 0};
    auto startInsertionIter = m_allNodes.insert(startNode).first;
    const Node& insertedStartNode = *startInsertionIter;
    m_activeNodes.insert(&insertedStartNode);

    while (true)
    {
        auto closestNodePtrIter = m_activeNodes.cbegin();
        const auto closestNodePtr = *closestNodePtrIter;
        m_activeNodes.erase(closestNodePtrIter);

        if (closestNodePtr->position == Coordinates{m_width - 1, m_height - 1} && closestNodePtr->numTilesMovedInDirection >= m_minNumMovesInSingleDirection)
        {
            m_minHeatLoss = closestNodePtr->pathCost;
            return;
        }

        for (const auto& neighborNode : getAllNeighborNodes(*closestNodePtr))
        {
            auto existingNeighborNodeIter = m_allNodes.find(neighborNode);

            if (existingNeighborNodeIter != m_allNodes.cend())
            {
                if (neighborNode.pathCost < existingNeighborNodeIter->pathCost)
                {
                    const Node& existingNeighborNode = *existingNeighborNodeIter;
                    m_activeNodes.erase(&existingNeighborNode);
                    existingNeighborNodeIter->pathCost = neighborNode.pathCost;
                    m_activeNodes.insert(&existingNeighborNode);
                }
            }
            else
            {
                auto neighborInsertionIter = m_allNodes.insert(neighborNode).first;
                const Node& insertedNeighborNode = *neighborInsertionIter;
                m_activeNodes.insert(&insertedNeighborNode);
            }
        }
    }
}

int CityBlockTraverser::getMinHeatLoss() const
{
    return m_minHeatLoss;
}

std::vector<Node> CityBlockTraverser::getAllNeighborNodes(const Node& baseNode) const
{
    std::vector<Node> allNeighborNodes;

    if (baseNode.numTilesMovedInDirection < m_maxNumMovesInSingleDirection)
    {
        auto maybeForwardsNode = getNodeInDirection(baseNode, baseNode.arrivalDirection, baseNode.numTilesMovedInDirection + 1);
        if (maybeForwardsNode)
        {
            allNeighborNodes.push_back(maybeForwardsNode.get());
        }
    }

    if (baseNode.numTilesMovedInDirection == 0 || baseNode.numTilesMovedInDirection >= m_minNumMovesInSingleDirection)
    {
        const Coordinates firstTurnDirection = {baseNode.arrivalDirection.second, baseNode.arrivalDirection.first};
        auto maybeFirstTurnNode = getNodeInDirection(baseNode, firstTurnDirection, 1);
        if (maybeFirstTurnNode)
        {
            allNeighborNodes.push_back(maybeFirstTurnNode.get());
        }


        const Coordinates secondTurnDirection = {-baseNode.arrivalDirection.second, -baseNode.arrivalDirection.first};
        auto maybeSecondTurnNode = getNodeInDirection(baseNode, secondTurnDirection, 1);
        if (maybeSecondTurnNode)
        {
            allNeighborNodes.push_back(maybeSecondTurnNode.get());
        }
    }

    return allNeighborNodes;
}

boost::optional<Node> CityBlockTraverser::getNodeInDirection(const Node& baseNode, const Coordinates& direction, int newNumTilesMovedInDirection) const
{
    const Coordinates newPosition{baseNode.position.first + direction.first, baseNode.position.second + direction.second};

    if (newPosition.first < 0 || newPosition.second < 0 || newPosition.first >= m_width || newPosition.second >= m_height)
    {
        return boost::none;
    }

    return Node{newPosition, direction, newNumTilesMovedInDirection, baseNode.pathCost + getCostAt(newPosition)};
}

int CityBlockTraverser::getCostAt(const Coordinates& coordinates) const
{
    return m_map.at(coordinates.second).at(coordinates.first);
}

}
}
}
