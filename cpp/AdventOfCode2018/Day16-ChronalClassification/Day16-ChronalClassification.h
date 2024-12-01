#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day16
{

unsigned numSamplesBehaveMoreThanThreeOpcodes(const std::vector<std::string>& opcodeManualLines);
unsigned valueInFirstRegisterAfterProgramFinishes(const std::vector<std::string>& opcodeManualLines);

}
}
}
