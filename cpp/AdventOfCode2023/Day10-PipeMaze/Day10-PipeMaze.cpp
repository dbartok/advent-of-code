#include "Day10-PipeMaze.h"

#include "PipeNetworkTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day10
{

int numStepsAlongMainLoopToFarthestPosition(const std::vector<std::string>& pipeNetworkLines)
{
    PipeNetworkTraverser pipeNetworkTraverser{pipeNetworkLines};

    pipeNetworkTraverser.traverseMainLoop();

    return pipeNetworkTraverser.getMainLoopLength() / 2;
}

int numTilesEnclosedByMainLoop(const std::vector<std::string>& pipeNetworkLines)
{
    PipeNetworkTraverser pipeNetworkTraverser{pipeNetworkLines};

    pipeNetworkTraverser.traverseMainLoop();

    return pipeNetworkTraverser.getNumTilesEnclosedByMainLoop();
}

}
}
}