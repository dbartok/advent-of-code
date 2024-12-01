#pragma once

#include "CoordinatesToNeighborCoordinates.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day20
{

class CoordinatesTraverser
{
public:
    CoordinatesTraverser(CoordinatesToNeighborCoordinates layoutMap, unsigned distanceThreshold);

    void traverse();

    unsigned getDistanceToFarthestCoordinate() const;
    unsigned getNumRoomsAboveDistanceThreshold() const;

private:
    CoordinatesToNeighborCoordinates m_layoutMap;
    CoordinatesSet m_visited;

    unsigned m_distanceThreshold;

    unsigned m_maxDistance = 0;
    unsigned m_numRoomsAboveDistanceThreshold = 0;
};

}
}
}
