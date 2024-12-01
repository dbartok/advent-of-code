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
namespace Day19
{

int sumOfRatingNumbersOfAllAcceptedParts(const std::vector<std::string>& systemLines);
int64_t numDistinctCombinationsAccepted(const std::vector<std::string>& systemLines);

}
}
}
