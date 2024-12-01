#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day13
{

int earliestBusIDMultipliedByWaitTime(int earliestDepartureTimestamp, const std::string& scheduleDescriptionString);
int64_t earliestTimestampWithMatchingDepartures(const std::string& scheduleDescriptionString);

}
}
}
