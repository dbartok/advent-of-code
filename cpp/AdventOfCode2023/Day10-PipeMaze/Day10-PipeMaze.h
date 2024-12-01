#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day10
{

int numStepsAlongMainLoopToFarthestPosition(const std::vector<std::string>& pipeNetworkLines);
int numTilesEnclosedByMainLoop(const std::vector<std::string>& pipeNetworkLines);

}
}
}
