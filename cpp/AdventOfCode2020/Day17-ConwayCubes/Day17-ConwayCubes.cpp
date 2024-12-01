#include "Day17-ConwayCubes.h"

#include "MultiDimensionalGameOfLifeSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char ACTIVE_CHAR = '#';
const size_t BOOT_CYCLE_LENGTH = 6;

}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day17
{

std::vector<MultiDimensionalVector> createStartingActiveCoordinatesVector(const std::vector<std::string>& initialStateLines, size_t numDimensions)
{
    std::vector<MultiDimensionalVector> startingActiveCoordinatesVector;

    for (int j = 0; j < initialStateLines.size(); ++j)
    {
        for (int i = 0; i < initialStateLines.at(j).size(); ++i)
        {
            if (initialStateLines.at(j).at(i) == ACTIVE_CHAR)
            {
                MultiDimensionalVector coordinates = MultiDimensionalVector::Zero(numDimensions);
                coordinates[0] = i;
                coordinates[1] = j;
                startingActiveCoordinatesVector.push_back(std::move(coordinates));
            }
        }
    }

    return startingActiveCoordinatesVector;
}

int numCubesInActiveStateAfterBootCycle3D(const std::vector<std::string>& initialStateLines)
{
    std::vector<MultiDimensionalVector> startingActiveCoordinatesVector = createStartingActiveCoordinatesVector(initialStateLines, 3);
    MultiDimensionalGameOfLifeSimulator simulator{std::move(startingActiveCoordinatesVector)};
    simulator.simulateRounds(BOOT_CYCLE_LENGTH);
    return simulator.getNumActiveCoordinates();
}

int numCubesInActiveStateAfterBootCycle4D(const std::vector<std::string>& initialStateLines)
{
    std::vector<MultiDimensionalVector> startingActiveCoordinatesVector = createStartingActiveCoordinatesVector(initialStateLines, 4);
    MultiDimensionalGameOfLifeSimulator simulator{std::move(startingActiveCoordinatesVector)};
    simulator.simulateRounds(BOOT_CYCLE_LENGTH);
    return simulator.getNumActiveCoordinates();
}

}
}
}
