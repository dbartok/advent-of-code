#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day13
{

unsigned severityOfWholeTrip(const std::vector<std::string>& scannerRangeLines);
unsigned smallestDelayNotToGetCaught(const std::vector<std::string>& scannerRangeLines);

}
}
}
