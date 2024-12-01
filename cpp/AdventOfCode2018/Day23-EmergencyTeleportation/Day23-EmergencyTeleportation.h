#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day23
{

unsigned numNanobotsInStrongestRange(const std::vector<std::string>& nanobotLines);
int lowestDistanceFromOriginWithMostNanobots(const std::vector<std::string>& nanobotLines);

}
}
}
