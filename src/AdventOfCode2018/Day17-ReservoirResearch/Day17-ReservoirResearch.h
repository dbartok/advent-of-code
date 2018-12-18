#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

unsigned numTilesWaterCanReach(const std::vector<std::string>& clayCoordinatesLines);
unsigned numTilesWaterRetained(const std::vector<std::string>& clayCoordinatesLines);

}
