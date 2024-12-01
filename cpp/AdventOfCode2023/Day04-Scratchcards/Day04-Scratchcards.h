#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day04
{

int numPointsWorthInTotal(const std::vector<std::string>& scratchcardLines);
int numTotalScratchcardsIncludingOriginalsAndCopies(const std::vector<std::string>& scratchcardLines);

}
}
}
