#include "Day12-HillClimbingAlgorithm.h"

#include "HillTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day12
{

int fewestStepsFromStartToEnd(const std::vector<std::string>& heightmapLines)
{
    HillTraverser hillTraverser{heightmapLines, {START_POSITION_CHAR}};

    hillTraverser.traverse();

    return hillTraverser.getMinStepsFromStartToEnd();
}

int fewestStepsFromAnyLowestElevationPointToEnd(const std::vector<std::string>& heightmapLines)
{
    HillTraverser hillTraverser{heightmapLines, {START_POSITION_CHAR, HEIGHT_AT_START}};

    hillTraverser.traverse();

    return hillTraverser.getMinStepsFromStartToEnd();
}

}
}
}