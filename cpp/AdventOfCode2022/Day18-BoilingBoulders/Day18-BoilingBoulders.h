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
namespace Day18
{

unsigned surfaceAreaOfScannedLavaDroplet(const std::vector<std::string>& lavaCubeCoordinatesLines);
unsigned outerSurfaceAreaOfScannedLavaDroplet(const std::vector<std::string>& lavaCubeCoordinatesLines);

}
}
}
