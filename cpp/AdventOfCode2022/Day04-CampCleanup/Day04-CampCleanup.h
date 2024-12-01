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
namespace Day04
{

int numAssignmentPairsFullyContainingEachOther(const std::vector<std::string>& assignmentPairLines);
int numAssignmentPairsOverlapping(const std::vector<std::string>& assignmentPairLines);

}
}
}
