#include "CoordinatesTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day20
{

CoordinatesTraverser::CoordinatesTraverser(CoordinatesToNeighborCoordinates layoutMap, unsigned distanceThreshold)
    : m_layoutMap{std::move(layoutMap)}
    , m_distanceThreshold(distanceThreshold)
{

}

void CoordinatesTraverser::traverse()
{
    std::queue<Coordinates> reachableNodesQueue;
    std::queue<Coordinates> nextReachableNodesQueue;
    reachableNodesQueue.push(Coordinates{0, 0});
    unsigned numNodesInPath = 0;

    while (!reachableNodesQueue.empty())
    {
        ++numNodesInPath;
        while (!reachableNodesQueue.empty())
        {
            Coordinates currentCoordinates = reachableNodesQueue.front();
            reachableNodesQueue.pop();

            CoordinatesSet neighbors;
            const auto findResult = m_layoutMap.find(currentCoordinates);
            if (findResult != m_layoutMap.end())
            {
                neighbors = findResult->second;
            }

            for (const auto& neighbor : neighbors)
            {
                if (m_visited.insert(neighbor).second)
                {
                    if (numNodesInPath >= m_distanceThreshold)
                    {
                        ++m_numRoomsAboveDistanceThreshold;
                    }

                    nextReachableNodesQueue.push(neighbor);
                }
            }
        }

        std::swap(reachableNodesQueue, nextReachableNodesQueue);
    }

    m_maxDistance = numNodesInPath - 1;
}

unsigned CoordinatesTraverser::getDistanceToFarthestCoordinate() const
{
    return m_maxDistance;
}

unsigned CoordinatesTraverser::getNumRoomsAboveDistanceThreshold() const
{
    return m_numRoomsAboveDistanceThreshold;
}

}
}
}
