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
namespace Day09
{

int sumOfForwardsExtrapolatedValues(const std::vector<std::string>& historyLines);
int sumOfBackwardsExtrapolatedValues(const std::vector<std::string>& historyLines);


}
}
}
