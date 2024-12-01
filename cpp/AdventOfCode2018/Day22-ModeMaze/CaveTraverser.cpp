#include "CaveTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day22
{

CaveTraverser::CaveTraverser(CaveMap caveMap)
    : m_caveMap{std::move(caveMap)}
{

}

void CaveTraverser::traverse()
{
    unsigned hScoreInitial = heuristicCostEstimate(START_COORDINATES, m_caveMap.getTargetCoordinates());
    Node startNode{START_COORDINATES, Equipment::TORCH, 0, hScoreInitial};
    Node targetNode{m_caveMap.getTargetCoordinates(), Equipment::TORCH, std::numeric_limits<unsigned>::max(), 0};

    std::unordered_set<Node, NodeHash> closedSet;
    std::unordered_set<Node, NodeHash> openSet{startNode};

    while (!openSet.empty())
    {
        Node currentNode = *std::min_element(openSet.cbegin(), openSet.cend(), [](const Node& lhs, const Node& rhs)
                                                {
                                                    return lhs.gScore + lhs.hScore < rhs.gScore + rhs.hScore;
                                                });

        if (currentNode == targetNode)
        {
            m_lowestCostToTarget = currentNode.gScore;
            return;
        }

        openSet.erase(currentNode);
        closedSet.insert(currentNode);

        for (const auto& adjacentNode : getAdjacentNodes(currentNode))
        {
            if (closedSet.find(adjacentNode) != closedSet.end())
            {
                continue;
            }

            auto findResult = openSet.find(adjacentNode);
            if (findResult == openSet.end())
            {
                openSet.insert(adjacentNode);
            }
            else if (adjacentNode.gScore < findResult->gScore)
            {
                openSet.erase(findResult);
                openSet.insert(adjacentNode);
            }
        }
    }
}

unsigned CaveTraverser::getLowestCostToTarget() const
{
    return m_lowestCostToTarget;
}

std::vector<Node> CaveTraverser::getAdjacentNodes(const Node& node)
{
    std::vector<Node> adjacentNodes;

    // Go to neighbor
    std::vector<Coordinates> allNeighborCoordinates = getAllNeighborCoordinates(node.coordinates);

    for (const auto& neighborCoordinates : allNeighborCoordinates)
    {
        unsigned riskLevel = m_caveMap.getRiskLevelAt(neighborCoordinates);
        if (isEquipmentCompatibleWithRiskLevel(node.equipment, riskLevel))
        {
            unsigned hScoreForNeighbor = heuristicCostEstimate(neighborCoordinates, m_caveMap.getTargetCoordinates());
            Node neighborNode{neighborCoordinates, node.equipment, node.gScore + 1, hScoreForNeighbor};
            adjacentNodes.push_back(neighborNode);
        }
    }

    // Change equipment
    Equipment newEquipment = getOtherValidEquipment(node);
    Node changedEquipmentNode{node.coordinates, newEquipment, node.gScore + EQUIPMENT_CHANGE_COST, node.hScore};
    adjacentNodes.push_back(changedEquipmentNode);

    return adjacentNodes;
}

std::vector<Coordinates> CaveTraverser::getAllNeighborCoordinates(const Coordinates& coordinates)
{
    std::vector<Coordinates> allNeighborCoordinates;

    if (coordinates.first > 0)
    {
        allNeighborCoordinates.emplace_back(coordinates.first - 1, coordinates.second);
    }
    if (coordinates.second > 0)
    {
        allNeighborCoordinates.emplace_back(coordinates.first, coordinates.second - 1);
    }
    allNeighborCoordinates.emplace_back(coordinates.first + 1, coordinates.second);
    allNeighborCoordinates.emplace_back(coordinates.first, coordinates.second + 1);

    return allNeighborCoordinates;
}

Equipment CaveTraverser::getOtherValidEquipment(const Node& node)
{
    unsigned riskLevel = m_caveMap.getRiskLevelAt(node.coordinates);
    switch (node.equipment)
    {
        case Equipment::CLIMBING_GEAR:
            return riskLevel == 0 ? Equipment::TORCH : Equipment::NOTHING;

        case Equipment::NOTHING:
            return riskLevel == 1 ? Equipment::CLIMBING_GEAR : Equipment::TORCH;

        case Equipment::TORCH:
            return riskLevel == 2 ? Equipment::NOTHING : Equipment::CLIMBING_GEAR;

        default:
            throw std::runtime_error("Invalid equipment.");
    }
}

unsigned CaveTraverser::heuristicCostEstimate(const Coordinates& start, const Coordinates& target)
{
    unsigned startY = start.first;
    unsigned startX = start.second;

    unsigned targetY = target.first;
    unsigned targetX = target.second;

    unsigned distanceY = std::max(startY, targetY) - std::min(startY, targetY);
    unsigned distanceX = std::max(startX, targetX) - std::min(startX, targetX);

    return distanceY + distanceX;
}

bool CaveTraverser::isEquipmentCompatibleWithRiskLevel(Equipment equipment, unsigned riskLevel)
{
    switch (equipment)
    {
        case Equipment::CLIMBING_GEAR:
            return riskLevel != 2;

        case Equipment::NOTHING:
            return riskLevel != 0;

        case Equipment::TORCH:
            return riskLevel != 1;

        default:
            throw std::runtime_error("Invalid equipment.");
    }
}

}
}
}
