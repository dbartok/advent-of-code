#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day06
{

using Coordinates = std::pair<unsigned, unsigned>;
using CoordinateIDType = char;
using CoordinateIDAndDistancePair = std::pair<CoordinateIDType, unsigned>;

class GridAreaAnalyzer
{
public:
    GridAreaAnalyzer(std::vector<Coordinates> allCoordinates);

    unsigned getLargestNonInfiniteArea() const;
    unsigned getAreaWithinGivenDistance(unsigned distanceThreshold) const;

private:
    std::unordered_map<CoordinateIDType, Coordinates> m_coordinateIDToCoordinates;
    Coordinates m_highestCoordinates;

    CoordinateIDType getClosestCoordinatesID(const Coordinates& origin) const;
    bool areCoordinatesWithinDistanceThreshold(const Coordinates& origin, unsigned distanceThreshold) const;
    std::vector<CoordinateIDAndDistancePair> getDistanceFromEachCoordinate(const Coordinates& origin) const;
};

}
}
}
