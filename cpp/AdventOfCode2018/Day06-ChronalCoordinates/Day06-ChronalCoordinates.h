#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
unsigned DEFAULT_DISTANCE_THRESHOLD = 10000;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day06
{

unsigned sizeOfLargestNonInfiniteArea(const std::vector<std::string>& coordinatesLines);
unsigned sizeOfAreaWithinGivenDistance(const std::vector<std::string>& coordinatesLines, unsigned distanceThreshold = DEFAULT_DISTANCE_THRESHOLD);

}
}
}
