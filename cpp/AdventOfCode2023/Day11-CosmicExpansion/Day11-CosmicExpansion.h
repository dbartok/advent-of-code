#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

int DEFAULT_LARGE_EXPANSION_RATE = 1'000'000;

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day11
{

int64_t sumOfShortestPathsBetweenAllPairs(const std::vector<std::string>& imageLines);
int64_t sumOfShortestPathsBetweenAllPairsWithLargerExpansionRate(const std::vector<std::string>& imageLines, int expansionRate = DEFAULT_LARGE_EXPANSION_RATE);

}
}
}
