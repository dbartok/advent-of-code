#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
unsigned DEFAULT_NUM_WORKERS = 5;
unsigned DEFAULT_ADDITIONAL_DURATION = 60;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day07
{

std::string topologicalOrderOfInstructions(const std::vector<std::string>& instructionLines);
unsigned timeUntilAllStepsAreDone(
    const std::vector<std::string>& instructionLines,
    unsigned numWorkers = DEFAULT_NUM_WORKERS,
    unsigned additionalDuration = DEFAULT_ADDITIONAL_DURATION);

}
}
}
