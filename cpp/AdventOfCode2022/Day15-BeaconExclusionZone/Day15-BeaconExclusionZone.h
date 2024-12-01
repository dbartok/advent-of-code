#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day15
{

unsigned numPositionsThatCannotContainBeaconInSpecificRow(const std::vector<std::string>& sensorAndBeaconPositionLines, int y);
int64_t distressBeaconTuningFrequency(const std::vector<std::string>& sensorAndBeaconPositionLines, int distressBeaconCoordinatesLowerBound, int distressBeaconCoordinatesUpperBound);

}
}
}
