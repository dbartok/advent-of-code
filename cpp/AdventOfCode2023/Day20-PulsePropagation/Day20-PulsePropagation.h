#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day20
{

int numLowAndHighPulsesMultipliedTogether(const std::vector<std::string>& moduleLines);
int64_t fewestNumButtonPressesToDeliverLowPulseToRx(const std::vector<std::string>& moduleLines);

}
}
}
