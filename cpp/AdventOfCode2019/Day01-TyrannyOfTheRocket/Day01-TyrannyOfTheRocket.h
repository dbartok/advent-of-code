#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day01
{

int getSumOfFuelRequirements(const std::vector<int>& moduleMasses);
int getSumOfFuelRequirementsIncludingFuelItself(const std::vector<int>& moduleMasses);

}
}
}
