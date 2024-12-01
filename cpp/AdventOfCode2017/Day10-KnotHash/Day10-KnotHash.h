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
namespace Day10
{

unsigned firstTwoMultipliedAfterKnotting(size_t listSize, const std::vector<unsigned>& lengths);
std::string knotHashDenseString(const std::string& stringToHash);

}
}
}
