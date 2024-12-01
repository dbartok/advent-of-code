#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day14
{

int64_t mostAndLeastCommonElementQuantityDifference(const std::vector<std::string>& polymerFormulaLines);
int64_t mostAndLeastCommonElementQuantityDifferenceReinforced(const std::vector<std::string>& polymerFormulaLines);

}
}
}
