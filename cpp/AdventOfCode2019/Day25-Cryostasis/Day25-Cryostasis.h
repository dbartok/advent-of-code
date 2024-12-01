#pragma once

#include "IntcodeTextAdventure.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day25
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;

std::string passwordForMainAirlock(const std::vector<IntcodeNumberType>& intcodeProgram);

}
}
}
