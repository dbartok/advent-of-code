#pragma once

#include "IntcodeComputerNetwork.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day23
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;

IntcodeNumberType secondPartOfFirstPacketAtSpecialAddress(const std::vector<IntcodeNumberType>& intcodeProgram);
IntcodeNumberType secondPartOfFirstDuplicateMessageByNat(const std::vector<IntcodeNumberType>& intcodeProgram);

}
}
}
