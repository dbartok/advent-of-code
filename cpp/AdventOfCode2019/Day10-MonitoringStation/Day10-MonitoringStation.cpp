#include "Day10-MonitoringStation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day10
{

CoordinatesSet createAsteroidCoordinatesSet(const std::vector<std::string> asteroidMapLines)
{
    CoordinatesSet asteroidCoordinatesSet;

    for (int j = 0; j < asteroidMapLines.size(); ++j)
    {
        for (int i = 0; i < asteroidMapLines.at(j).size(); ++i)
        {
            if (asteroidMapLines.at(j).at(i) == '#')
            {
                asteroidCoordinatesSet.emplace(i, j);
            }
        }
    }

    return asteroidCoordinatesSet;
}

unsigned maxNumAsteroidsDetected(const std::vector<std::string> asteroidMapLines)
{
    CoordinatesSet asteroidCoordinatesSet = createAsteroidCoordinatesSet(asteroidMapLines);

    AsteroidMap asteroidMap{asteroidCoordinatesSet};

    return asteroidMap.getMaxNumAsteroidsDetected();
}

std::vector<Coordinates> vaporizationOrder(const std::vector<std::string> asteroidMapLines)
{
    CoordinatesSet asteroidCoordinatesSet = createAsteroidCoordinatesSet(asteroidMapLines);

    AsteroidMap asteroidMap{asteroidCoordinatesSet};

    return asteroidMap.vaporize();
}

}
}
}
