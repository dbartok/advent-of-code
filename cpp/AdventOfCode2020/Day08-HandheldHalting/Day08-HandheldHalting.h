#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day08
{

int valueInAccAfterFirstDuplicateInstruction(const std::vector<std::string>& instructionLines);
int valueInAccAfterRepairedProgramTerminates(const std::vector<std::string>& instructionLines);

}
}
}
