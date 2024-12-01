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
namespace Day12
{

int distanceToEndLocationShipMoves(const std::vector<std::string>& instructionLines);
int distanceToEndLocationWaypointMoves(const std::vector<std::string>& instructionLines);

}
}
}
