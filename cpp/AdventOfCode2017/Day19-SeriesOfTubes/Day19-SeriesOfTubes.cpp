#include "Day19-SeriesOfTubes.h"

#include "PipeDiagramTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day19
{

std::string lettersVisited(const std::vector<std::string>& diagramLines)
{
    PipeDiagramTraverser pipeDiagramTraverser{diagramLines};
    pipeDiagramTraverser.traverse();
    return pipeDiagramTraverser.getLettersVisitedSequence();
}

unsigned totalNumStepsForPacket(const std::vector<std::string>& diagramLines)
{
    PipeDiagramTraverser pipeDiagramTraverser{diagramLines};
    pipeDiagramTraverser.traverse();
    return pipeDiagramTraverser.getNumStepsTaken();
}

}
}
}
