#pragma once

#include <AdventOfCode2019/Day05-SunnyWithAsteroids/IntcodeInterpreter.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day21
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;

IntcodeNumberType amountOfHullDamage(const std::vector<IntcodeNumberType>& intcodeProgram);
IntcodeNumberType amountOfHullDamageExtendedSensors(const std::vector<IntcodeNumberType>& intcodeProgram);

}
}
}
