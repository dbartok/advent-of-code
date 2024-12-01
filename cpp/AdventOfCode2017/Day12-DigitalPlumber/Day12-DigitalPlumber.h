#pragma once

#include "VillageGraph.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day12
{

unsigned numNodesInGroupNodeZero(const std::vector<std::string>& neighborsLines);
unsigned numTotalGroups(const std::vector<std::string>& neighborsLines);

}
}
}
