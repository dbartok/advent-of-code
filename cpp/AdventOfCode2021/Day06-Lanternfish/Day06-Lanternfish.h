#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day06
{

uint64_t numLanternfishAfterSmallNumberOfDays(const std::vector<int>& initialState);
uint64_t numLanternfishAfterLargeNumberOfDays(const std::vector<int>& initialState);

}
}
}
