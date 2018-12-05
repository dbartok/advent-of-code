#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

unsigned guardMostMinutesAsleepTimesMinute(const std::vector<std::string>& eventLines);
unsigned guardMostFrequentlyMinuteAsleepTimesMinute(const std::vector<std::string>& eventLines);

}
