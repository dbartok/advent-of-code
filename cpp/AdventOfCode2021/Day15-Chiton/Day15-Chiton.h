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
namespace Day15
{

int lowestTotalRiskOfAnyPath(const std::vector<std::string>& riskLevelLines);
int lowestTotalRiskOfAnyPathRepeatedMap(const std::vector<std::string>& riskLevelLines);

}
}
}
