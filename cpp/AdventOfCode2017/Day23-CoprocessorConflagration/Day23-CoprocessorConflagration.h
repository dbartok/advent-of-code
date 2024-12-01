#pragma once

#include "HandOptimizedAssembly.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day23
{

unsigned numTimesMultInvoked(const std::vector<std::string>& instructionStrings);
unsigned overheatFinalValueOfH() noexcept;

}
}
}
