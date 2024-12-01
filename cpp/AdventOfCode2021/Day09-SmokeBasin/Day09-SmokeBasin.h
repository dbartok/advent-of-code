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
namespace Day09
{

int sumOfRiskLevelsOfAllLowPoints(const std::vector<std::string>& heightmapLines);
int multipleOfThreeLargestBasinSizes(const std::vector<std::string>& heightmapLines);

}
}
}
