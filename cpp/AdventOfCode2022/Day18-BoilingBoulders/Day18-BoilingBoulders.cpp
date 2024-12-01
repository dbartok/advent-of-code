#include "Day18-BoilingBoulders.h"

#include "LavaDropletAnalyzer.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day18
{

Coordinates parseLavaCubeCoordinatesLine(const std::string& lavaCubeCoordinatesLine)
{
    std::vector<int> coordinates;
    Utils::splitStringIntoTypedVector(lavaCubeCoordinatesLine, coordinates, ',');

    return Coordinates{coordinates.at(0), coordinates.at(1), coordinates.at(2)};
}

std::vector<Coordinates> parseLavaCubeCoordinatesLines(const std::vector<std::string>& lavaCubeCoordinatesLines)
{
    std::vector<Coordinates> allLavaCubeCoordinates;

    for (const auto& lavaCubeCoordinatesLine : lavaCubeCoordinatesLines)
    {
        Coordinates lavaCubeCoordinates = parseLavaCubeCoordinatesLine(lavaCubeCoordinatesLine);
        allLavaCubeCoordinates.push_back(std::move(lavaCubeCoordinates));
    }

    return allLavaCubeCoordinates;
}

unsigned surfaceAreaOfScannedLavaDroplet(const std::vector<std::string>& lavaCubeCoordinatesLines)
{
    std::vector<Coordinates> allLavaCubeCoordinates = parseLavaCubeCoordinatesLines(lavaCubeCoordinatesLines);

    LavaDropletAnalyzer lavaDropletAnalyzer{std::move(allLavaCubeCoordinates)};

    return lavaDropletAnalyzer.getSurfaceArea();
}

unsigned outerSurfaceAreaOfScannedLavaDroplet(const std::vector<std::string>& lavaCubeCoordinatesLines)
{
    std::vector<Coordinates> allLavaCubeCoordinates = parseLavaCubeCoordinatesLines(lavaCubeCoordinatesLines);

    LavaDropletAnalyzer lavaDropletAnalyzer{std::move(allLavaCubeCoordinates)};

    return lavaDropletAnalyzer.getOuterSurfaceArea();
}

}
}
}