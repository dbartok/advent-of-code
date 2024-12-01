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
namespace Day20
{

int64_t cornerTileIDsMultiplied(const std::vector<std::string>& cameraArrayLines);
int numWaterNotPartOfASeaMonster(const std::vector<std::string>& cameraArrayLines);

}
}
}
