#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day19
{

unsigned numBeacons(const std::vector<std::string>& allBeaconPositionsLines);
unsigned largestManhattanDistanceBetweenAnyTwoScanners(const std::vector<std::string>& allBeaconPositionsLines);

}
}
}
