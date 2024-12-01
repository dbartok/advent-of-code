#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day07
{

int leastAmountOfFuelSpentToAlign(const std::vector<int>& horizontalPositions);
int leastAmountOfFuelSpentToAlignWithIncreasingCosts(const std::vector<int>& horizontalPositions);

}
}
}
