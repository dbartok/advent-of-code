#pragma once

#include "OxygenRepairDroid.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day15
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;

int fewestNumberOfMovementsToOxygen(const std::vector<IntcodeNumberType>& intcodeProgram);
int numMinutesUntilOxygenSpreads(const std::vector<IntcodeNumberType>& intcodeProgram);

}
}
}
