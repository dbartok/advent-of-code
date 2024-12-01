#include "ForestTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day23
{

ForestTraverser::ForestTraverser(std::vector<std::string> map)
    : m_map{std::move(map)}
    , m_width{m_map.front().size()}
    , m_height{m_map.size()}
    , m_start{1, 0}
    , m_end{m_width - 2, m_height - 1}
{

}

void ForestTraverser::traverse()
{
    createCompactAdjacencyMatrix();

    std::queue<LongestPathBfsNode> queue;
    queue.emplace(0, 0, std::unordered_set<int>{0});

    while (!queue.empty())
    {
        LongestPathBfsNode currentNode = queue.front();
        queue.pop();

        if (currentNode.junctionIndex == m_compactAdjacencyMatrix.size() - 1)
        {
            m_longestPathLength = std::max(m_longestPathLength, currentNode.totalDistance);
        }
        else
        {
            for (int neighborCandidateIndex = 0; neighborCandidateIndex < m_compactAdjacencyMatrix.size(); ++neighborCandidateIndex)
            {
                if (currentNode.visited.find(neighborCandidateIndex) != currentNode.visited.cend())
                {
                    continue;
                }

                const int distanceToNeighbor = m_compactAdjacencyMatrix.at(currentNode.junctionIndex).at(neighborCandidateIndex);
                if (distanceToNeighbor > 0)
                {
                    auto newVisited{currentNode.visited};
                    newVisited.insert(neighborCandidateIndex);
                    queue.emplace(neighborCandidateIndex, currentNode.totalDistance + distanceToNeighbor, std::move(newVisited));
                }
            }
        }
    }
}

int ForestTraverser::getLongestPathLength() const
{
    return m_longestPathLength;
}

void ForestTraverser::createCompactAdjacencyMatrix()
{
    std::vector<Coordinates> allJunctionCoordinates = getAllJunctionCoordinates();

    for (int i = 0; i < allJunctionCoordinates.size(); ++i)
    {
        m_junctionCoordinatesToIndex.emplace(allJunctionCoordinates.at(i), i);
    }

    m_compactAdjacencyMatrix.resize(allJunctionCoordinates.size(), std::vector<int>(allJunctionCoordinates.size(), -1));

    for (const auto& junctionCoordinates : allJunctionCoordinates)
    {
        populateCompactAdjacencyMatrixForJunction(junctionCoordinates);
    }
}

void ForestTraverser::populateCompactAdjacencyMatrixForJunction(const Coordinates& startingJunctionCoordinates)
{
    const int sourceJunctionIndex = m_junctionCoordinatesToIndex.at(startingJunctionCoordinates);

    std::queue<CoordinatesAndDistance> queue;
    queue.emplace(startingJunctionCoordinates, 0);
    std::unordered_set<Coordinates, boost::hash<Coordinates>> visited;
    visited.insert(startingJunctionCoordinates);

    while (!queue.empty())
    {
        CoordinatesAndDistance currentCoordinatesAndDistance = queue.front();
        queue.pop();

        auto junctionCoordinatesAndIndexIter = m_junctionCoordinatesToIndex.find(currentCoordinatesAndDistance.coordinates);
        if (junctionCoordinatesAndIndexIter != m_junctionCoordinatesToIndex.cend() && junctionCoordinatesAndIndexIter->first != startingJunctionCoordinates)
        {
            const int destinationJunctionIndex = junctionCoordinatesAndIndexIter->second;
            m_compactAdjacencyMatrix.at(sourceJunctionIndex).at(destinationJunctionIndex) = currentCoordinatesAndDistance.distance;
        }
        else
        {
            std::vector<Coordinates> allReachableNeighborCoordinates = getAllReachableNeighborCoordinates(currentCoordinatesAndDistance.coordinates);

            for (const auto& neighboorCoordinates : allReachableNeighborCoordinates)
            {
                if (visited.insert(neighboorCoordinates).second)
                {
                    queue.emplace(neighboorCoordinates, currentCoordinatesAndDistance.distance + 1);
                }
            }
        }
    }
}

std::vector<Coordinates> ForestTraverser::getAllJunctionCoordinates() const
{
    std::vector<Coordinates> allJunctionCoordinates{m_start};

    for (size_t j = 0; j < m_height; ++j)
    {
        for (size_t i = 0; i < m_width; ++i)
        {
            if (getTileAt({i, j}) == FOREST)
            {
                continue;
            }

            std::vector<Coordinates> allNonForestNeighborCoordinates = getAllNonForestNeighborCoordinates({i, j});

            if (allNonForestNeighborCoordinates.size() > 2)
            {
                allJunctionCoordinates.emplace_back(i, j);
            }
        }
    }

    allJunctionCoordinates.push_back(m_end);

    return allJunctionCoordinates;
}

std::vector<Coordinates> ForestTraverser::getAllNonForestNeighborCoordinates(const Coordinates& baseCoordinates) const
{
    const std::vector<Coordinates> possibleNeighborCoordinates =
    {
        Coordinates{baseCoordinates.first, baseCoordinates.second - 1},
        Coordinates{baseCoordinates.first, baseCoordinates.second + 1},
        Coordinates{baseCoordinates.first - 1, baseCoordinates.second},
        Coordinates{baseCoordinates.first + 1, baseCoordinates.second}
    };

    std::vector<Coordinates> allNonForestNeighborCoordinates;

    std::copy_if(possibleNeighborCoordinates.cbegin(),
                    possibleNeighborCoordinates.cend(),
                    std::back_inserter(allNonForestNeighborCoordinates),
                    [this, baseCoordinates](const auto& neighborCoordinates)
                    {
                        return this->isInbounds(neighborCoordinates) && this->getTileAt(neighborCoordinates) != FOREST;
                    });

    return allNonForestNeighborCoordinates;
}

std::vector<Coordinates> ForestTraverser::getAllReachableNeighborCoordinates(const Coordinates& baseCoordinates) const
{
    std::vector<Coordinates> allNonForestNeighborCoordinates = getAllNonForestNeighborCoordinates(baseCoordinates);

    std::vector<Coordinates> allReachableNeighborCoordinates;

    std::copy_if(allNonForestNeighborCoordinates.cbegin(),
                    allNonForestNeighborCoordinates.cend(),
                    std::back_inserter(allReachableNeighborCoordinates),
                    [this, baseCoordinates](const auto& neighborCoordinates)
                    {
                        return this->isValidStepFromBaseToNeighbor(baseCoordinates, neighborCoordinates);
                    });

    return allReachableNeighborCoordinates;
}

bool ForestTraverser::isInbounds(const Coordinates& coordinates) const
{
    return coordinates.first >= 0 && coordinates.first < m_width&& coordinates.second >= 0 && coordinates.second < m_height;
}

bool ForestTraverser::isValidStepFromBaseToNeighbor(const Coordinates& baseCoordinates, const Coordinates& neighborCoordinates) const
{
    const char neighborTile = getTileAt(neighborCoordinates);

    if (neighborTile == FOREST)
    {
        return false;
    }

    if (neighborTile == PATH)
    {
        return true;
    }

    const Coordinates step = {neighborCoordinates.first - baseCoordinates.first, neighborCoordinates.second - baseCoordinates.second};

    if (step == UP && neighborTile == UP_SLOPE)
    {
        return true;
    }

    if (step == DOWN && neighborTile == DOWN_SLOPE)
    {
        return true;
    }

    if (step == LEFT && neighborTile == LEFT_SLOPE)
    {
        return true;
    }

    if (step == RIGHT && neighborTile == RIGHT_SLOPE)
    {
        return true;
    }

    return false;
}

char ForestTraverser::getTileAt(const Coordinates& coordinates) const
{
    return m_map.at(coordinates.second).at(coordinates.first);
}

}
}
}
