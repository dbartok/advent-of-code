#pragma once

#include "ArcadeCabinet.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day13
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;

unsigned numBlockTilesWhenGameExits(const std::vector<IntcodeNumberType>& intcodeProgram);
unsigned scoreAfterLastBlockBroken(const std::vector<IntcodeNumberType>& intcodeProgram);

}
}
}
