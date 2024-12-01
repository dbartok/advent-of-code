#include "HeightmapAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <iterator>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int MAX_HEIGHT = 9;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day09
{

HeightmapAnalyzer::HeightmapAnalyzer(Heightmap heightmap)
    : m_heightmap{std::move(heightmap)}
    , m_width{m_heightmap.at(0).size()}
    , m_height{m_heightmap.size()}
{

}

int HeightmapAnalyzer::getSumOfRiskLevelsOfAllLowPoints() const
{
    const std::vector<Coordinates> allLowPointCoordinates = getAllLowPointCoordinates();

    return std::accumulate(allLowPointCoordinates.cbegin(), allLowPointCoordinates.cend(), 0, [this](const auto& acc, const auto& point)
                            {
                                return acc + this->getHeightAt(point) + 1;
                            });
}

int HeightmapAnalyzer::getMultipleOfThreeLargestBasinSizes() const
{
    std::vector<int> basinSizes = getBasinSizes();
    std::sort(basinSizes.begin(), basinSizes.end(), std::greater<int>());
    return basinSizes.at(0) * basinSizes.at(1) * basinSizes.at(2);
}

std::vector<Coordinates> HeightmapAnalyzer::getAllLowPointCoordinates() const
{
    std::vector<Coordinates> lowPointCoordinates;

    for (size_t j = 0; j < m_height; ++j)
    {
        for (size_t i = 0; i < m_width; ++i)
        {
            Coordinates currentCoordinates{i, j};
            if (isLowPoint(currentCoordinates))
            {
                lowPointCoordinates.push_back(currentCoordinates);
            }
        }
    }

    return lowPointCoordinates;
}

bool HeightmapAnalyzer::isLowPoint(const Coordinates& coordinates) const
{
    const std::vector<Coordinates> allAdjacentLocationCoordinates = getAllAdjacentLocationCoordinates(coordinates);
    const int currentHeight = getHeightAt(coordinates);

    return std::all_of(allAdjacentLocationCoordinates.cbegin(), allAdjacentLocationCoordinates.cend(), [this, currentHeight](const auto& adjacentLocationCoordinates)
                        {
                            return currentHeight < this->getHeightAt(adjacentLocationCoordinates);
                        });
}

int HeightmapAnalyzer::getHeightAt(const Coordinates& coordinates) const
{
    return m_heightmap.at(coordinates.second).at(coordinates.first);
}

std::vector<Coordinates> HeightmapAnalyzer::getAllAdjacentLocationCoordinates(const Coordinates& baseCoordinates) const
{
    const std::vector<Coordinates> possibleAdjacentLocationCoordinates =
    {
        Coordinates{baseCoordinates.first, baseCoordinates.second - 1},
        Coordinates{baseCoordinates.first, baseCoordinates.second + 1},
        Coordinates{baseCoordinates.first - 1, baseCoordinates.second},
        Coordinates{baseCoordinates.first + 1, baseCoordinates.second}
    };

    std::vector<Coordinates> inBoundsAdjacentLocationCoordinates;

    std::copy_if(possibleAdjacentLocationCoordinates.cbegin(),
                    possibleAdjacentLocationCoordinates.cend(),
                    std::back_inserter(inBoundsAdjacentLocationCoordinates),
                    [this](const auto& coords)
                    {
                        return this->isInBounds(coords);
                    });

    return inBoundsAdjacentLocationCoordinates;
}

bool HeightmapAnalyzer::isInBounds(const Coordinates& coordinates) const
{
    return coordinates.first >= 0 && coordinates.first < m_width&& coordinates.second >= 0 && coordinates.second < m_height;
}

std::vector<int> HeightmapAnalyzer::getBasinSizes() const
{
    const std::vector<Coordinates> allLowPointCoordinates = getAllLowPointCoordinates();

    std::vector<int> basinSizes;

    for (const auto& lowPointCoordinates : allLowPointCoordinates)
    {
        const int basinSize = getBasinSizeAt(lowPointCoordinates);
        basinSizes.push_back(basinSize);
    }

    return basinSizes;
}

int HeightmapAnalyzer::getBasinSizeAt(const Coordinates& startCoordinates) const
{
    CoordinatesSet visitedCoordinates;
    return getBasinSizeAtRecursive(startCoordinates, visitedCoordinates);
}

int HeightmapAnalyzer::getBasinSizeAtRecursive(const Coordinates& startCoordinates, CoordinatesSet& visitedCoordinates) const
{
    const auto insertResult = visitedCoordinates.insert(startCoordinates);
    if (!insertResult.second)
    {
        return 0;
    }

    const std::vector<Coordinates> allAdjacentLocationCoordinates = getAllAdjacentLocationCoordinates(startCoordinates);

    int basinSizeStartingFromAdjacentLocations = 0;
    for (const auto& adjacentLocationCoordinates : allAdjacentLocationCoordinates)
    {
        const int adjacentLocationHeight = getHeightAt(adjacentLocationCoordinates);
        if (adjacentLocationHeight >= getHeightAt(startCoordinates) && adjacentLocationHeight != MAX_HEIGHT)
        {
            basinSizeStartingFromAdjacentLocations += getBasinSizeAtRecursive(adjacentLocationCoordinates, visitedCoordinates);
        }
    }

    return basinSizeStartingFromAdjacentLocations + 1;

}

}
}
}
