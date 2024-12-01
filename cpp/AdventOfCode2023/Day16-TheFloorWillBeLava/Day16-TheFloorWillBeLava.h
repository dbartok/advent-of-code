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
namespace Day16
{

int numEnergizedTiles(const std::vector<std::string>& contraptionLines);
int maxNumEnergizedTiles(const std::vector<std::string>& contraptionLines);

}
}
}
