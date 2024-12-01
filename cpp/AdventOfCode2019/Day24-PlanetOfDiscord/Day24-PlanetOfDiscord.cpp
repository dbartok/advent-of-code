#include "Day24-PlanetOfDiscord.h"

#include "BugCellularAutomaton.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day24
{

Layout createLayout(const std::vector<std::string>& layoutLines)
{
    Layout layout;

    for (int j = 0; j < layoutLines.size(); ++j)
    {
        for (int i = 0; i < layoutLines.at(j).size(); ++i)
        {
            if (layoutLines.at(j).at(i) == '#')
            {
                layout.emplace(0, Coordinates{i, j});
            }
        }
    }

    return layout;
}

int biodiversityRatingOfFirstDuplicateLayout(const std::vector<std::string>& initialLayoutLines)
{
    Layout initialLayout = createLayout(initialLayoutLines);

    BugCellularAutomaton automaton{initialLayout, GRID_SIZE};

    automaton.simulateUntilFirstDuplicate();

    return automaton.getCurrentBiodiversity();
}

unsigned numBugsAfterSimulationRecursiveGrid(const std::vector<std::string>& initialLayoutLines, unsigned numSteps)
{
    Layout initialLayout = createLayout(initialLayoutLines);

    BugCellularAutomaton automaton{initialLayout, GRID_SIZE};

    automaton.simulateStepsRecursiveGrid(numSteps);

    return automaton.getNumBugs();
}

}
}
}
