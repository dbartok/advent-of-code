#include "LavaDropletAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day18
{

LavaDropletAnalyzer::LavaDropletAnalyzer(std::vector<Coordinates> allLavaCubeCoordinates)
{
    m_allLavaCubeCoordinates.insert(std::make_move_iterator(allLavaCubeCoordinates.begin()), std::make_move_iterator(allLavaCubeCoordinates.end()));

    const auto bounds = getBounds();
    m_lowerBound = bounds.first;
    m_upperBound = bounds.second;
}

unsigned LavaDropletAnalyzer::getSurfaceArea() const
{
    unsigned surfaceArea = m_allLavaCubeCoordinates.size() * 6;

    for (const auto& lavaCubeCoordinates : m_allLavaCubeCoordinates)
    {
        const std::vector<Coordinates> allNeighborCoordinates = getAllNeighborCoordinates(lavaCubeCoordinates);
        const unsigned numLavaCubeNeighbors = std::count_if(allNeighborCoordinates.cbegin(), allNeighborCoordinates.cend(), [this](const auto& neighborCoords)
                                                            {
                                                                return this->m_allLavaCubeCoordinates.find(neighborCoords) != this->m_allLavaCubeCoordinates.cend();
                                                            });
        surfaceArea -= numLavaCubeNeighbors;
    }

    return surfaceArea;
}

unsigned LavaDropletAnalyzer::getOuterSurfaceArea() const
{
    std::queue<Coordinates> bfsQueue;
    bfsQueue.push(m_lowerBound);
    CoordinatesSet visited{m_lowerBound};
    unsigned numLavaCubeSidesEncountered = 0;

    while (!bfsQueue.empty())
    {
        const Coordinates currentCoordinates = bfsQueue.front();
        bfsQueue.pop();

        std::vector<Coordinates> allInBoundsNeighborCoordinates = getInBoundsNeighborCoordinates(currentCoordinates);

        for (const auto& neighborCoordinates : allInBoundsNeighborCoordinates)
        {
            if (m_allLavaCubeCoordinates.find(neighborCoordinates) != m_allLavaCubeCoordinates.cend())
            {
                ++numLavaCubeSidesEncountered;
            }
            else if (visited.insert(neighborCoordinates).second)
            {
                bfsQueue.push(neighborCoordinates);
            }
        }
    }

    return numLavaCubeSidesEncountered;
}

std::vector<Coordinates> LavaDropletAnalyzer::getInBoundsNeighborCoordinates(const Coordinates& coordinates) const
{
    std::vector<Coordinates> allNeighborCoordinates = getAllNeighborCoordinates(coordinates);

    std::vector<Coordinates> inBoundsNeighborCoordinates;

    std::copy_if(std::make_move_iterator(allNeighborCoordinates.begin()), std::make_move_iterator(allNeighborCoordinates.end()), std::back_inserter(inBoundsNeighborCoordinates), [this](const auto& coords)
                    {
                        for (size_t i = 0; i < NUM_DIMENSIONS; ++i)
                        {
                            const int currentCoordinate = coords.at(i);
                            const int lowerBoundForCoordinate = this->m_lowerBound.at(i);
                            const int upperBoundForCoordinate = this->m_upperBound.at(i);

                            if (currentCoordinate < lowerBoundForCoordinate || currentCoordinate > upperBoundForCoordinate)
                            {
                                return false;
                            }
                        }

                        return true;
                    });

    return inBoundsNeighborCoordinates;
}

std::pair<Coordinates, Coordinates> LavaDropletAnalyzer::getBounds() const
{
    Coordinates lowerBoundCoordinates;
    Coordinates upperBoundsCoordinates;

    for (int i = 0; i < NUM_DIMENSIONS; ++i)
    {
        const auto minmaxIter = std::minmax_element(m_allLavaCubeCoordinates.cbegin(), m_allLavaCubeCoordinates.cend(), [i](const Coordinates& lhs, const Coordinates& rhs)
                                                    {
                                                        return lhs.at(i) < rhs.at(i);
                                                    });

        const int min = minmaxIter.first->at(i);
        const int max = minmaxIter.second->at(i);

        // Leave an extra offset of 1 around the min and the max
        // This is to make sure that we also discover the outermost sides of the droplet in our search
        lowerBoundCoordinates.at(i) = min - 1;
        upperBoundsCoordinates.at(i) = max + 1;
    }

    return {std::move(lowerBoundCoordinates), std::move(upperBoundsCoordinates)};
}

std::vector<Coordinates> LavaDropletAnalyzer::getAllNeighborCoordinates(const Coordinates& coordinates)
{
    const int x = coordinates.at(0);
    const int y = coordinates.at(1);
    const int z = coordinates.at(2);

    return std::vector<Coordinates>
    {
        {x + 1, y, z},
        {x - 1, y, z},
        {x, y + 1, z},
        {x, y - 1, z},
        {x, y, z + 1},
        {x, y, z - 1},
    };
}

}
}
}
