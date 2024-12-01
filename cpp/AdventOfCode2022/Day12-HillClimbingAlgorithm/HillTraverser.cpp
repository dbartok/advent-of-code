#include "HillTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_set>
#include <algorithm>
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day12
{

HillTraverser::HillTraverser(Heightmap heightmap, std::unordered_set<char> possibleStartChars)
    : m_heightmap{std::move(heightmap)}
    , m_height{m_heightmap.size()}
    , m_width{m_heightmap.at(0).size()}
{
    for (size_t j = 0; j < m_height; ++j)
    {
        for (size_t i = 0; i < m_width; ++i)
        {
            if (possibleStartChars.find(heightAt({i, j})) != possibleStartChars.cend())
            {
                m_allPossibleStartCoordinates.push_back({i, j});
                heightAt({i, j}) = HEIGHT_AT_START;
            }

            if (heightAt({i, j}) == END_POSITION_CHAR)
            {
                m_endCoordinates = {i, j};
                heightAt({i, j}) = HEIGHT_AT_END;
            }
        }
    }
}

void HillTraverser::traverse()
{
    for (const auto& startCoordinates : m_allPossibleStartCoordinates)
    {
        traverseFromSingleStartingPoint(startCoordinates);
    }
}

int HillTraverser::getMinStepsFromStartToEnd() const
{
    return m_minStepsFromStartToEnd;
}

void HillTraverser::traverseFromSingleStartingPoint(const Coordinates& startCoordinates)
{
    std::queue<BfsNode> bfsQueue;
    bfsQueue.push({startCoordinates, 0});

    std::unordered_set<Coordinates, boost::hash<Coordinates>> visitedCoordinates;
    visitedCoordinates.insert(startCoordinates);

    while (!bfsQueue.empty())
    {
        const BfsNode currentNode = bfsQueue.front();
        bfsQueue.pop();

        if (currentNode.coordinates == m_endCoordinates)
        {
            m_minStepsFromStartToEnd = std::min(m_minStepsFromStartToEnd, currentNode.numSteps);
            break;
        }

        const std::vector<Coordinates> allReachableNeighborCoordinates = getAllReachableNeighborCoordinates(currentNode.coordinates);

        for (const auto& reachableNeighborCoordinates : allReachableNeighborCoordinates)
        {
            const bool isPreviouslyUnseen = visitedCoordinates.insert(reachableNeighborCoordinates).second;
            if (isPreviouslyUnseen)
            {
                bfsQueue.push({reachableNeighborCoordinates, currentNode.numSteps + 1});
            }
        }
    }
}

std::vector<Coordinates> HillTraverser::getAllReachableNeighborCoordinates(const Coordinates& baseCoordinates) const
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
                    [this, baseCoordinates](const auto& neighborCoords)
                    {
                        return this->isInBounds(neighborCoords) && this->isNeighborReachableFromNode(baseCoordinates, neighborCoords);
                    });

    return inBoundsNeighborCoordinates;
}

bool HillTraverser::isNeighborReachableFromNode(const Coordinates& baseCoordinates, const Coordinates& neighborCoordinates) const
{
    const char baseHeight = heightAt(baseCoordinates);
    const char neighborHeight = heightAt(neighborCoordinates);

    return neighborHeight - baseHeight <= 1;
}

bool HillTraverser::isInBounds(const Coordinates& coordinates) const
{
    return coordinates.first >= 0 && coordinates.first < m_width&& coordinates.second >= 0 && coordinates.second < m_height;
}

const char& HillTraverser::heightAt(const Coordinates& coordinates) const
{
    return m_heightmap.at(coordinates.second).at(coordinates.first);
}

char& HillTraverser::heightAt(const Coordinates& coordinates)
{
    return const_cast<char&>(static_cast<const HillTraverser&>(*this).heightAt(coordinates));
}

}
}
}
