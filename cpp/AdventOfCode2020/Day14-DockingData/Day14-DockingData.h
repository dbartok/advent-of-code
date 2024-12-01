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
namespace Day14
{

uint64_t sumOfValuesInMemoryAfterCompletion(const std::vector<std::string>& instructionLines);
uint64_t sumOfValuesInMemoryAfterDecoderCompletion(const std::vector<std::string>& instructionLines);

}
}
}
