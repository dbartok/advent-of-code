#include "Day20-ARegularMap.h"

#include "RoomLayoutRegexParser.h"
#include "CoordinatesTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day20
{

CoordinatesTraverser parseCoordinatesTraverser(const std::string& roomLayoutRegex, unsigned distanceThreshold = 0)
{
    RoomLayoutRegexParser roomLayoutRegexParser{roomLayoutRegex};
    roomLayoutRegexParser.parse();

    auto layoutMap = roomLayoutRegexParser.getLayoutMap();

    return CoordinatesTraverser{std::move(layoutMap), distanceThreshold};
}

unsigned distanceToFarthestRoom(const std::string& roomLayoutRegex)
{
    CoordinatesTraverser coordinatesTraverser = parseCoordinatesTraverser(roomLayoutRegex);
    coordinatesTraverser.traverse();

    return coordinatesTraverser.getDistanceToFarthestCoordinate();
}

unsigned numRoomsWithLargeDistance(const std::string& roomLayoutRegex, unsigned distanceThreshold)
{
    CoordinatesTraverser coordinatesTraverser = parseCoordinatesTraverser(roomLayoutRegex, distanceThreshold);
    coordinatesTraverser.traverse();

    return coordinatesTraverser.getNumRoomsAboveDistanceThreshold();
}

}
}
}
