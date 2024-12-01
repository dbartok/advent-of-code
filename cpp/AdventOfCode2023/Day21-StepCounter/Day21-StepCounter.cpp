#include "Day21-StepCounter.h"

#include "GardenTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day21
{

// Calculate value at x according to Lagrange interpolation based on an array of known points in the function
// https://en.wikipedia.org/wiki/Polynomial_interpolation#Constructing_the_interpolation_polynomial
int64_t getInterpolatedValue(std::vector<Coordinates> knownPoints, int x)
{
    int64_t interpolatedValue = 0;

    for (int i = 0; i < knownPoints.size(); ++i)
    {
        int64_t currentTerm = 1;

        for (int j = 0; j < knownPoints.size(); ++j)
        {
            if (j != i)
            {
                currentTerm *= (x - knownPoints.at(j).first) / (knownPoints.at(i).first - knownPoints.at(j).first);
            }
        }

        currentTerm *= knownPoints.at(i).second;
        interpolatedValue += currentTerm;
    }

    return interpolatedValue;
}

int numGardenPlotsReachableAfterSteps(const std::vector<std::string>& mapLines, int numSteps)
{
    GardenTraverser gardenTraverser{mapLines};

    gardenTraverser.traverse(numSteps);

    return gardenTraverser.getNumReachablePositions();
}

int64_t numGardenPlotsReachableAfterSeveralSteps(const std::vector<std::string>& mapLines, int numSteps)
{
    const int gridSize = mapLines.size();
    const int offset = gridSize / 2;

    assert(numSteps % gridSize == offset);

    std::vector<Coordinates> firstFewCoordinatesOfGrowthFunction;
    for (int x = 0; x < 3; ++x)
    {
        const unsigned numCurrentSteps = x * gridSize + offset;

        GardenTraverser gardenTraverser{mapLines};
        gardenTraverser.traverse(numCurrentSteps);
        const int numReachablePositions = gardenTraverser.getNumReachablePositions();

        firstFewCoordinatesOfGrowthFunction.emplace_back(x, numReachablePositions);
    }

    const int desiredXCoordinateOfGrowthFunction = (numSteps - offset) / gridSize;

    return getInterpolatedValue(firstFewCoordinatesOfGrowthFunction, desiredXCoordinateOfGrowthFunction);
}

}
}
}