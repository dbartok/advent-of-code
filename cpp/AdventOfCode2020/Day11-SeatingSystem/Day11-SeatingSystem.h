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
namespace Day11
{

int numOccupiedSeatsWithAdjacencyRules(std::vector<std::string> seatLayoutLines);
int numOccupiedSeatsWithVisibilityRules(std::vector<std::string> seatLayoutLines);

}
}
}
