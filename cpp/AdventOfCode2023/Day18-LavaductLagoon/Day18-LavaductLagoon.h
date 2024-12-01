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
namespace Day18
{

int64_t amountOfLavaHeld(const std::vector<std::string>& digPlanLines);
int64_t amountOfLavaHeldWithSwappedInstructions(const std::vector<std::string>& digPlanLines);

}
}
}
