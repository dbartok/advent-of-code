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
namespace Day23
{

int numStepsInLongestHike(const std::vector<std::string>& forestMapLines);
int numStepsInLongestHikeWithoutSlopes(const std::vector<std::string>& forestMapLines);

}
}
}
