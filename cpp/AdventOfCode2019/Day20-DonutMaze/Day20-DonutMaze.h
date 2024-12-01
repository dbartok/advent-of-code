#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day20
{

int numStepsToExit(const std::vector<std::string>& donutMazeLines);
int numStepsToExitWithMatchingLayers(const std::vector<std::string>& donutMazeLines);

}
}
}
