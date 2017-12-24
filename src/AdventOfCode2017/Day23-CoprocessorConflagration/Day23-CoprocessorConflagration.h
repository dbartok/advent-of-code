#pragma once

#include "HandOptimizedAssembly.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

unsigned numTimesMultInvoked(const std::vector<std::string>& instructionStrings);
unsigned overheatFinalValueOfH() noexcept;

}
