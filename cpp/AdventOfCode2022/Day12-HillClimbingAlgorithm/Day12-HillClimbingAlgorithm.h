#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day12
{

int fewestStepsFromStartToEnd(const std::vector<std::string>& heightmapLines);
int fewestStepsFromAnyLowestElevationPointToEnd(const std::vector<std::string>& heightmapLines);

}
}
}
