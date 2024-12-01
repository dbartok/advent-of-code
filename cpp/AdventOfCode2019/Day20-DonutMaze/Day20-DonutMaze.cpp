#include "Day20-DonutMaze.h"

#include "DonutMazeParser.h"
#include "DonutMazeTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day20
{

DonutMaze createDonutMaze(const std::vector<std::string>& donutMazeLines)
{
    DonutMazeParser parser{donutMazeLines};
    parser.parse();
    return parser.getDonutMaze();
}

int numStepsToExit(const std::vector<std::string>& donutMazeLines)
{
    DonutMazeTraverser traverser{createDonutMaze(donutMazeLines)};

    traverser.traverse();

    return traverser.getShortestPathLength();
}

int numStepsToExitWithMatchingLayers(const std::vector<std::string>& donutMazeLines)
{
    DonutMazeTraverser traverser{createDonutMaze(donutMazeLines), TraverseMode::RESPECT_LAYERS};

    traverser.traverse();

    return traverser.getShortestPathLength();
}

}
}
}
