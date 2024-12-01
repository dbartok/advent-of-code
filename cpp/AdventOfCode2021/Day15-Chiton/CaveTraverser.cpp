#include "CaveTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day15
{

CaveTraverser::CaveTraverser(const RiskLevelMap& riskLevelMap)
    : m_width{riskLevelMap.at(0).size()}
    , m_height(riskLevelMap.size())
{
    for (int j = 0; j < m_width; ++j)
    {
        for (int i = 0; i < m_height; ++i)
        {
            Coordinates coordinates{i, j};
            Node node{coordinates, riskLevelMap.at(j).at(i), std::numeric_limits<int>::max()};
            m_coordinatesToNode.insert({std::move(coordinates), std::move(node)});
        }
    }
}

void CaveTraverser::traverse()
{
    Node& startNode = m_coordinatesToNode.at({0, 0});
    startNode.bestPathCostSoFar = 0;
    m_activeNodePtrs.insert(&startNode);

    while (!m_activeNodePtrs.empty())
    {
        Node* closestNodePtr = *m_activeNodePtrs.begin();
        m_activeNodePtrs.erase(closestNodePtr);

        if (isDestination(closestNodePtr->coordinates))
        {
            m_MinRiskLevel = closestNodePtr->bestPathCostSoFar;
            return;
        }

        for (const auto& neighborCoordinates : getAllNeighborCoordinates(closestNodePtr->coordinates))
        {
            Node& neighborNode = m_coordinatesToNode.at(neighborCoordinates);
            const int pathToNeighborCost = closestNodePtr->bestPathCostSoFar + neighborNode.riskLevel;
            if (pathToNeighborCost < neighborNode.bestPathCostSoFar)
            {
                m_activeNodePtrs.erase(&neighborNode);
                neighborNode.bestPathCostSoFar = pathToNeighborCost;
                m_activeNodePtrs.insert(&neighborNode);
            }
        }
    }
}

int CaveTraverser::getMinRiskLevel() const
{
    return m_MinRiskLevel;
}

std::vector<Coordinates> CaveTraverser::getAllNeighborCoordinates(const Coordinates& baseCoordinates) const
{
    const std::vector<Coordinates> possibleNeighborCoordinates =
    {
        Coordinates{baseCoordinates.first, baseCoordinates.second - 1},
        Coordinates{baseCoordinates.first, baseCoordinates.second + 1},
        Coordinates{baseCoordinates.first - 1, baseCoordinates.second},
        Coordinates{baseCoordinates.first + 1, baseCoordinates.second}
    };

    std::vector<Coordinates> inBoundsNeighborCoordinates;

    std::copy_if(possibleNeighborCoordinates.cbegin(),
                    possibleNeighborCoordinates.cend(),
                    std::back_inserter(inBoundsNeighborCoordinates),
                    [this](const auto& coords)
                    {
                        return this->isInBounds(coords);
                    });

    return inBoundsNeighborCoordinates;
}

bool CaveTraverser::isInBounds(const Coordinates& coordinates) const
{
    return m_coordinatesToNode.find(coordinates) != m_coordinatesToNode.cend();
}

bool CaveTraverser::isDestination(const Coordinates& coordinates) const
{
    return coordinates.first == m_width - 1 && coordinates.second == m_height - 1;
}

}
}
}
