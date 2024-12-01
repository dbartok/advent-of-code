#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

int DEFAULT_DESIRED_OUTPUT = 19690720;

}

namespace AdventOfCode
{
namespace Year2019
{
namespace Day02
{

int getValueInPositionZeroAfterProgramHalts(std::vector<int> intcodeProgram, int noun, int verb);
int getScoreOfNounAndVerbForSpecificOutput(std::vector<int> intcodeProgram, int desiredOutput = DEFAULT_DESIRED_OUTPUT);

}
}
}
