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
namespace Day12
{

int64_t sumOfAllPossibleArrangements(const std::vector<std::string>& springConditionsLines);
int64_t sumOfAllPossibleArrangementsUnfolded(const std::vector<std::string>& springConditionsLines);

}
}
}
