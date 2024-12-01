#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day15
{

int nthNumberSpokenSmallN(const std::vector<int>& startingNumbers);
int nthNumberSpokenLargeN(const std::vector<int>& startingNumbers);

}
}
}
