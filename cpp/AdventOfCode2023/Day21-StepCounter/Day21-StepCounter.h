#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

int NUM_STEPS_PART_ONE = 64;
int NUM_STEPS_PART_TWO = 26501365;

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day21
{

int numGardenPlotsReachableAfterSteps(const std::vector<std::string>& mapLines, int numSteps = NUM_STEPS_PART_ONE);
int64_t numGardenPlotsReachableAfterSeveralSteps(const std::vector<std::string>& mapLines, int numSteps = NUM_STEPS_PART_TWO);

}
}
}
