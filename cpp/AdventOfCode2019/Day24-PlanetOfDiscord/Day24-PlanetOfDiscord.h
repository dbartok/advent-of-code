#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day24
{

int biodiversityRatingOfFirstDuplicateLayout(const std::vector<std::string>& initialLayoutLines);
unsigned numBugsAfterSimulationRecursiveGrid(const std::vector<std::string>& initialLayoutLines, unsigned numSteps);

}
}
}
