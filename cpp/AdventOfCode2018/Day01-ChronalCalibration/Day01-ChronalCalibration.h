#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day01
{

int sumOfAllNumbers(const std::vector<int>& numbers);
int firstDuplicateSumReached(const std::vector<int>& numbers);

}
}
}
