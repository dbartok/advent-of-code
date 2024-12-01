#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const double TEST_AREA_MIN = 200000000000000;
const double TEST_AREA_MAX = 400000000000000;

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day24
{

int numXYIntersectionsWithinTestArea(const std::vector<std::string>& hailstoneLines, double testAreaMin = TEST_AREA_MIN, double testAreaMax = TEST_AREA_MAX);
int64_t sumOfCoordinatesOfIniitialRockPosition(const std::vector<std::string>& hailstoneLines);

}
}
}
