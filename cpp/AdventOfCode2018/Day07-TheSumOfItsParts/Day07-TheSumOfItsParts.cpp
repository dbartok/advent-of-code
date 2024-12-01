#include "Day07-TheSumOfItsParts.h"

#include "DependencyGraph.h"
#include "DependencyScheduler.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day07
{

DependencyGraph parseDependencyGraphFromInstructionLines(const std::vector<std::string>& instructionLines)
{
    DependencyGraph graph;

    for (const auto& line : instructionLines)
    {
        std::regex guardIDRegex("[Ss]tep ([A-Z])");
        std::smatch matchResults;

        std::regex_search(line, matchResults, guardIDRegex);
        NodeIDType from = matchResults[1].str().front();

        std::string suffix = matchResults.suffix();
        std::regex_search(suffix, matchResults, guardIDRegex);
        NodeIDType to = matchResults[1].str().front();

        graph.addEdge(std::move(from), std::move(to));
    }

    return graph;
}

std::string topologicalOrderOfInstructions(const std::vector<std::string>& instructionLines)
{
    DependencyGraph dependencyGraph = parseDependencyGraphFromInstructionLines(instructionLines);

    return dependencyGraph.getTopologicalOrder();
}

unsigned timeUntilAllStepsAreDone(const std::vector<std::string>& instructionLines, unsigned numWorkers, unsigned additionalDuration)
{
    DependencyGraph dependencyGraph = parseDependencyGraphFromInstructionLines(instructionLines);
    DependencyScheduler scheduler{std::move(dependencyGraph), numWorkers, additionalDuration};

    scheduler.completeAllWork();

    return scheduler.getNumElapsedSteps();
}

}
}
}
