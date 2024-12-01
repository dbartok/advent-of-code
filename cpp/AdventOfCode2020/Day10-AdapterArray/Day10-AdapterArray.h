#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day10
{

int numOneAndThreeJoltDifferencesMultiplied(std::vector<int> joltageRatings);
int64_t numDistinctAdapterArrangements(std::vector<int> joltageRatings);

}
}
}
