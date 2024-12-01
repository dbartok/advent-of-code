#include "BlizzardPathfinder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day24
{

BlizzardPathfinder::BlizzardPathfinder(BlizzardMap blizzardMap, unsigned startTime)
    : m_blizzardMap{std::move(blizzardMap)}
    , m_startTime{startTime}
    , m_minTimeElapsedToReachGoal{std::numeric_limits<unsigned>::max()}
{

}

void BlizzardPathfinder::findShortestPath()
{
    const auto cmp = [this](const Node& lhs, const Node& rhs)
    {
        return lhs.timeElapsed + lhs.remainingTimeLowerBound > rhs.timeElapsed + rhs.remainingTimeLowerBound;
    };

    const Node startNode{m_blizzardMap.startPosition, m_startTime, getRemainingTimeLowerBound(m_blizzardMap.startPosition)};

    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> openNodesPriorityQueue(cmp);
    openNodesPriorityQueue.push(startNode);
    std::unordered_set<Node, NodeHash> seenNodes{startNode};

    while (!openNodesPriorityQueue.empty())
    {
        const Node currentNode = openNodesPriorityQueue.top();
        openNodesPriorityQueue.pop();

        if (currentNode.position == m_blizzardMap.endPosition)
        {
            m_minTimeElapsedToReachGoal = currentNode.timeElapsed;
            break;
        }

        const std::vector<Node> neighborNodes = getNeighborNodes(currentNode);

        for (const auto& neighborNode : neighborNodes)
        {
            if (seenNodes.insert(neighborNode).second)
            {
                openNodesPriorityQueue.push(neighborNode);
            }
        }
    }
}

unsigned BlizzardPathfinder::getMinTimeElapsedSinceStartToReachGoal() const
{
    return m_minTimeElapsedToReachGoal - m_startTime;
}

unsigned BlizzardPathfinder::getRemainingTimeLowerBound(const Coordinates& coordinates) const
{
    return std::abs(m_blizzardMap.endPosition.first - coordinates.first) + std::abs(m_blizzardMap.endPosition.second - coordinates.second);
}

std::vector<BlizzardPathfinder::Node> BlizzardPathfinder::getNeighborNodes(const Node& currentNode) const
{
    const auto& currentPosition = currentNode.position;
    std::vector<Coordinates> possibleNextPositions =
    {
        {currentPosition.first + 1, currentPosition.second},
        {currentPosition.first - 1, currentPosition.second},
        {currentPosition.first, currentPosition.second + 1},
        {currentPosition.first, currentPosition.second - 1},
        {currentPosition.first, currentPosition.second}, // Wait in place
    };
    unsigned timeElapsedAfterMove = currentNode.timeElapsed + 1;

    std::vector<Node> neighborNodes;

    for (const auto& possibleNextPosition : possibleNextPositions)
    {
        if (isPositionFreeAtTime(possibleNextPosition, timeElapsedAfterMove))
        {
            neighborNodes.emplace_back(possibleNextPosition, timeElapsedAfterMove, getRemainingTimeLowerBound(possibleNextPosition));
        }
    }

    return neighborNodes;
}

bool BlizzardPathfinder::isPositionFreeAtTime(const Coordinates& position, unsigned time) const
{
    if (position == m_blizzardMap.startPosition || position == m_blizzardMap.endPosition)
    {
        return true;
    }

    if (position.first < 1 || position.first >= m_blizzardMap.width - 1 || position.second < 1 || position.second >= m_blizzardMap.height - 1)
    {
        return false;
    }

    // Vertical blizzards
    if (!isPositionBlizzardFreeAtTime(m_blizzardMap.xCoordinateToBlizzards, position.first, position.second, time, m_blizzardMap.height))
    {
        return false;
    }

    // Horizontal blizzards
    if (!isPositionBlizzardFreeAtTime(m_blizzardMap.yCoordinateToBlizzards, position.second, position.first, time, m_blizzardMap.width))
    {
        return false;
    }

    return true;
}

bool BlizzardPathfinder::isPositionBlizzardFreeAtTime(const CoordinateToBlizzards& coordinateToBlizzards, int blizzardMapKey, int positionToCheck, unsigned time, unsigned arrayLength)
{
    auto blizzardsIter = coordinateToBlizzards.find(blizzardMapKey);

    if (blizzardsIter == coordinateToBlizzards.end())
    {
        return true;
    }

    const auto& blizzards = blizzardsIter->second;

    for (const auto& blizzard : blizzards)
    {
        const int blizzardAbsolutePositionWithoutWrapping = blizzard.initialOffset + blizzard.velocity * time;
        const int blizzardPositionRelativeToBoundWithoutWrapping = blizzardAbsolutePositionWithoutWrapping - 1;
        const int wrappingLength = arrayLength - 2;
        const int wrappedBlizzardCoordinateRelativeToBound = mod(blizzardPositionRelativeToBoundWithoutWrapping, wrappingLength);
        const int currentBlizzardCoordinate = wrappedBlizzardCoordinateRelativeToBound + 1;

        if (positionToCheck == currentBlizzardCoordinate)
        {
            return false;
        }
    }

    return true;
}

int BlizzardPathfinder::mod(int a, int b)
{
    int m = a % b;

    if (m < 0)
    {
        m += b;
    }

    return m;
}

}
}
}
