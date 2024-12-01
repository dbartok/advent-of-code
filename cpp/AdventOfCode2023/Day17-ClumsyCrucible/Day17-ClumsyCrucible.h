#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day17
{

int leastHeatLossIncurred(const std::vector<std::string>& mapLines);
int leastHeatLossIncurredForUltraCrucible(const std::vector<std::string>& mapLines);

}
}
}
