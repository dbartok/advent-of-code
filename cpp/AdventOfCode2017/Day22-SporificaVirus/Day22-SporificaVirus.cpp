#include "Day22-SporificaVirus.h"

#include "GridInfectingVirus.h"
#include <AdventOfCode2017/Day03-SpiralMemory/InfiniteGrid.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day22
{

InfiniteGrid<InfectionState> createInfiniteGridFromVirusPosLines(const std::vector<std::string>& virusPosLine)
{
    InfiniteGrid<InfectionState> grid;

    const int gridSize = virusPosLine.size();
    const int middleOffset = virusPosLine.size() / 2;

    for (int j = 0; j < gridSize; ++j)
    {
        for (int i = 0; i < gridSize; ++i)
        {
            if (virusPosLine[j][i] == '#')
            {
                grid.setValue(i - middleOffset, j - middleOffset, InfectionState::INFECTED);
            }
        }
    }

    return grid;
}

unsigned basicVirusInfectingBursts(const std::vector<std::string>& initialVirusPosLines, unsigned numIterations)
{
    InfiniteGrid<InfectionState> initialGrid = createInfiniteGridFromVirusPosLines(initialVirusPosLines);

    BasicGridInfectingVirus basicVirus{initialGrid};
    basicVirus.infectRepeatedly(numIterations);
    return basicVirus.getTotalInfectionBursts();
}

unsigned evolvedVirusInfectingBursts(const std::vector<std::string>& initialVirusPosLines, unsigned numIterations)
{
    InfiniteGrid<InfectionState> initialGrid = createInfiniteGridFromVirusPosLines(initialVirusPosLines);

    EvolvedGridInfectingVirus evolvedVirus{initialGrid};
    evolvedVirus.infectRepeatedly(numIterations);
    return evolvedVirus.getTotalInfectionBursts();
}

}
}
}
