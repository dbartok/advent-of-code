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
namespace Day09
{

int numPositionsVisitedByTail(const std::vector<std::string>& motionLines);
int numPositionsVisitedByTailWithLongerRope(const std::vector<std::string>& motionLines);

}
}
}
