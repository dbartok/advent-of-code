#include "GardenTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

char START = 'S';
char ROCK = '#';

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day21
{

GardenTraverser::GardenTraverser(std::vector<std::string> map)
    : m_map{std::move(map)}
    , m_width{m_map.front().size()}
    , m_height{m_map.size()}
{
    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            if (getSoilTypeAt({i, j}) == START)
            {
                m_startCoordinates = {i, j};
            }
        }
    }
}

void GardenTraverser::traverse(int numSteps)
{
    CoordinatesSet currentReachableCoordinatesQueue;
    CoordinatesSet nextReachableCoordinatesQueue;
    nextReachableCoordinatesQueue.insert(m_startCoordinates);

    for (int step = 0; step < numSteps; ++step)
    {
        std::swap(currentReachableCoordinatesQueue, nextReachableCoordinatesQueue);

        while (!currentReachableCoordinatesQueue.empty())
        {
            const Coordinates currentCoordinates = *currentReachableCoordinatesQueue.begin();
            currentReachableCoordinatesQueue.erase(currentReachableCoordinatesQueue.begin());

            std::vector<Coordinates> allReachableNeighborCoordinates = getAllReachableNeighborCoordinates(currentCoordinates);

            for (const auto& reachableNeighborCoordinates : allReachableNeighborCoordinates)
            {
                nextReachableCoordinatesQueue.insert(reachableNeighborCoordinates);
            }
        }
    }

    m_numReachablePositions = nextReachableCoordinatesQueue.size();
}

int GardenTraverser::getNumReachablePositions() const
{
    return m_numReachablePositions;
}

std::vector<Coordinates> GardenTraverser::getAllReachableNeighborCoordinates(const Coordinates& baseCoordinates)
{
    const std::vector<Coordinates> possibleNeighborCoordinates =
    {
        Coordinates{baseCoordinates.first, baseCoordinates.second - 1},
        Coordinates{baseCoordinates.first, baseCoordinates.second + 1},
        Coordinates{baseCoordinates.first - 1, baseCoordinates.second},
        Coordinates{baseCoordinates.first + 1, baseCoordinates.second}
    };

    std::vector<Coordinates> reachableNeighborCoordinates;

    std::copy_if(possibleNeighborCoordinates.cbegin(),
                    possibleNeighborCoordinates.cend(),
                    std::back_inserter(reachableNeighborCoordinates),
                    [this](const auto& neighborCoords)
                    {
                        return this->getSoilTypeAt(neighborCoords) != ROCK;
                    });

    return reachableNeighborCoordinates;
}

char GardenTraverser::getSoilTypeAt(const Coordinates& coordinates) const
{
    return m_map.at(mod(coordinates.second, m_height)).at(mod(coordinates.first, m_width));
}

int GardenTraverser::mod(int dividend, int divisor)
{
    int modulus = dividend % divisor;

    if (modulus < 0)
    {
        modulus += divisor;
    }

    return modulus;
}

}
}
}
