#include "Day11-DumboOctopus.h"

#include "OctopusGridSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <iterator>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const size_t NUM_STEPS_PART_ONE = 100;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day11
{

EnergyLevelRow parseEnergyLevelLine(const std::string& energyLevelLine)
{
    EnergyLevelRow energyLevelRow;

    std::transform(energyLevelLine.cbegin(), energyLevelLine.cend(), std::back_inserter(energyLevelRow), [](const char c)
                   {
                       return c - '0';
                   });

    return energyLevelRow;
}

EnergyLevelGrid parseEnergyLevelLines(const std::vector<std::string>& energyLevelLines)
{
    EnergyLevelGrid energyLevelGrid;

    for (const auto& line : energyLevelLines)
    {
        EnergyLevelRow energyLevelRow = parseEnergyLevelLine(line);
        energyLevelGrid.push_back(std::move(energyLevelRow));
    }

    return energyLevelGrid;
}

unsigned numTotalFlashes(const std::vector<std::string>& initialEnergyLevelLines)
{
    EnergyLevelGrid initialEnergyLevelGrid = parseEnergyLevelLines(initialEnergyLevelLines);
    OctopusGridSimulator octopusGridSimulator{std::move(initialEnergyLevelGrid)};
    octopusGridSimulator.simulate(NUM_STEPS_PART_ONE);
    return octopusGridSimulator.getNumTotalFlashes();
}

unsigned numStepsUntilSynchonizedFlash(const std::vector<std::string>& initialEnergyLevelLines)
{
    EnergyLevelGrid initialEnergyLevelGrid = parseEnergyLevelLines(initialEnergyLevelLines);
    OctopusGridSimulator octopusGridSimulator{std::move(initialEnergyLevelGrid)};
    octopusGridSimulator.simulateUntilSynchronizedFlash();
    return octopusGridSimulator.getNumStepsElapsed();
}

}
}
}
