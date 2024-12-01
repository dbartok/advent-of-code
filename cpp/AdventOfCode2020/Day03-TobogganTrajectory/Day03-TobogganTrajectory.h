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
namespace Day03
{

int64_t numTreesEncounteredSingleSlope(const std::vector<std::string>& gridLines);
int64_t numTreesEncounteredMultipleSlopes(const std::vector<std::string>& gridLines);

}
}
}
