#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
int PART_TWO_ROLLING_WINDOW_SIZE = 3;
}


namespace AdventOfCode
{
namespace Year2021
{
namespace Day01
{

unsigned numDepthMeasurementIncreases(const std::vector<unsigned>& depthMeasurements);
unsigned numDepthMeasurementIncreasesWithRollingWindow(const std::vector<unsigned>& depthMeasurements, int rollingWindowSize = PART_TWO_ROLLING_WINDOW_SIZE);

}
}
}
