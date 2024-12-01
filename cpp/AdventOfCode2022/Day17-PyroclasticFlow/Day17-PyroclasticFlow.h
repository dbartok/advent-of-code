#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day17
{

int64_t towerHeightAfterRocksStoppedFalling(const std::string& jetPatternString);
int64_t towerHeightAfterRocksStoppedFallingWithManyRocks(const std::string& jetPatternString);

}
}
}
