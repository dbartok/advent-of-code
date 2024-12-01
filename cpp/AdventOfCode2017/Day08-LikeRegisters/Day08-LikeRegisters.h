#pragma once

#include "Instruction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day08
{

int largestRegisterAfterCompletion(const std::vector<Instruction>& instructions);
int largestRegisterDuringExecution(const std::vector<Instruction>& instructions);

}
}
}
