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
namespace Day08
{

int numTreesVisibleFromOutsideTheGrid(const std::vector<std::string>& heightmapLines);
int highestPossibleScenicScore(const std::vector<std::string>& heightmapLines);

}
}
}
