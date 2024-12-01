#pragma once

#include <AdventOfCode2019/Day05-SunnyWithAsteroids/IntcodeInterpreter.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day09
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;

std::vector<IntcodeNumberType> boostKeycodeProduced(const std::vector<IntcodeNumberType>& intcodeProgram, int input);

}
}
}
