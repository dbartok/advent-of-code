#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day21
{

int64_t numberYelledByRootMonkey(const std::vector<std::string>& monkeyLines);
int64_t numberYelledByHumanToPassEqualityTest(const std::vector<std::string>& monkeyLines);

}
}
}
