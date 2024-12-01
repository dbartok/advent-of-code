#include "Day23-UnstableDiffusion.h"

#include "ElfMovementSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned NUM_DAYS_TO_SIMULATE_FIRST_PART = 10;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day23
{

unsigned numGroundTilesInBoundingRectangle(const std::vector<std::string>& initialPositionsLines)
{
    ElfMovementSimulator elfMovementSimulator{initialPositionsLines};

    elfMovementSimulator.simulate(NUM_DAYS_TO_SIMULATE_FIRST_PART);

    return elfMovementSimulator.getNumGroundTilesInBoundingRectangle();
}

unsigned numFirstRoundWhereNoElfMoves(const std::vector<std::string>& initialPositionsLines)
{
    ElfMovementSimulator elfMovementSimulator{initialPositionsLines};

    elfMovementSimulator.simulate();

    return elfMovementSimulator.getNumFirstRoundWhereNoElfMoves();
}

}
}
}