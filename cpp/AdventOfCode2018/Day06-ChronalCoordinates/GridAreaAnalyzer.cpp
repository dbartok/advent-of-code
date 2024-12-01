#pragma once

#include "GridAreaAnalyzer.h"

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include<vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const AdventOfCode::Year2018::Day06::CoordinateIDType NO_CLAIM_COORDINATE_ID = '.';
const AdventOfCode::Year2018::Day06::CoordinateIDType STARTING_COORDINATE_ID = 'a';
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day06
{

GridAreaAnalyzer::GridAreaAnalyzer(std::vector<Coordinates> allCoordinates)
    : m_coordinateIDToCoordinates{}
    , m_highestCoordinates{0, 0}
{
    CoordinateIDType coordinateID = STARTING_COORDINATE_ID;
    for (auto& coordinates : allCoordinates)
    {
        m_highestCoordinates.first = std::max(m_highestCoordinates.first, coordinates.first);
        m_highestCoordinates.second = std::max(m_highestCoordinates.second, coordinates.second);

        m_coordinateIDToCoordinates.emplace(coordinateID++, std::move(coordinates));
    }
}

unsigned GridAreaAnalyzer::getLargestNonInfiniteArea() const
{
    std::unordered_map<char, unsigned> coordinateIDToArea;
    std::unordered_set<CoordinateIDType> closestToEdgeCoordinateIDs;

    for (unsigned i = 0; i <= m_highestCoordinates.first; ++i)
    {
        for (unsigned j = 0; j <= m_highestCoordinates.second; ++j)
        {
            const CoordinateIDType coordID = getClosestCoordinatesID({i, j});
            ++coordinateIDToArea[coordID];

            // We collect coordinates that are the closest to at least one point on the edge
            // These are the ones that have infinite area
            if (i == 0 || j == 0 || i == m_highestCoordinates.first || j == m_highestCoordinates.second)
            {
                closestToEdgeCoordinateIDs.insert(coordID);
            }
        }
    }

    // Remove coordinates with infinite area
    for (const auto& edgeID : closestToEdgeCoordinateIDs)
    {
        coordinateIDToArea.erase(edgeID);
    }

    auto maxIter = std::max_element(coordinateIDToArea.begin(), coordinateIDToArea.end(),
                                    [](const auto& lhs, const auto& rhs) noexcept
                                    {
                                        return lhs.second < rhs.second;
                                    });

    return maxIter->second;
}

unsigned GridAreaAnalyzer::getAreaWithinGivenDistance(unsigned distanceThreshold) const
{
    unsigned areaSize = 0;
    for (unsigned i = 0; i <= m_highestCoordinates.first; ++i)
    {
        for (unsigned j = 0; j <= m_highestCoordinates.second; ++j)
        {
            if (areCoordinatesWithinDistanceThreshold({i, j}, distanceThreshold))
            {
                ++areaSize;
            }
        }
    }

    return areaSize;
}

CoordinateIDType GridAreaAnalyzer::getClosestCoordinatesID(const Coordinates& origin) const
{
    std::vector<CoordinateIDAndDistancePair> coordinateIDAndDistances = getDistanceFromEachCoordinate(origin);

    std::nth_element(coordinateIDAndDistances.begin(), coordinateIDAndDistances.begin() + 1, coordinateIDAndDistances.end(),
                     [](const auto& lhs, const auto& rhs) noexcept
                     {
                         return lhs.second < rhs.second;
                     });

    const auto& maxElem = coordinateIDAndDistances[0];
    const auto& secondMaxElem = coordinateIDAndDistances[1];

    if (maxElem.second == secondMaxElem.second)
    {
        return NO_CLAIM_COORDINATE_ID;
    }

    return maxElem.first;
}

bool GridAreaAnalyzer::areCoordinatesWithinDistanceThreshold(const Coordinates& origin, unsigned distanceThreshold) const
{
    std::vector<CoordinateIDAndDistancePair> distanceFromEachCoordinate = getDistanceFromEachCoordinate(origin);

    const unsigned totalDistance = std::accumulate(distanceFromEachCoordinate.cbegin(), distanceFromEachCoordinate.cend(), 0u,
                                             [](unsigned acc, const auto& elem) noexcept
                                             {
                                                 return acc + elem.second;
                                             });

    return totalDistance < distanceThreshold;
}

std::vector<CoordinateIDAndDistancePair> GridAreaAnalyzer::getDistanceFromEachCoordinate(const Coordinates& origin) const
{
    std::vector<CoordinateIDAndDistancePair> distanceFromEachCoordinate;

    for (const auto& coordinateIDAndCoorindates : m_coordinateIDToCoordinates)
    {
        CoordinateIDType coordinateID;
        Coordinates coordinates;

        std::tie(coordinateID, coordinates) = coordinateIDAndCoorindates;

        const unsigned distanceX = std::max(origin.first, coordinates.first) - std::min(origin.first, coordinates.first);
        const unsigned distanceY = std::max(origin.second, coordinates.second) - std::min(origin.second, coordinates.second);

        unsigned manhattanDistance = distanceX + distanceY;

        distanceFromEachCoordinate.emplace_back(coordinateID, manhattanDistance);
    }

    return distanceFromEachCoordinate;
}

}
}
}
