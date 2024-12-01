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
namespace Day05
{

int numPointsWhereHorizontalOrVerticalLinesOverlap(const std::vector<std::string>& ventLines);
int numPointsWhereLinesOverlap(const std::vector<std::string>& ventLines);

}
}
}
