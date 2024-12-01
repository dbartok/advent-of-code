#include "Day09-SensorBoost.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day09
{

using AdventOfCode::Year2019::Day05::IntcodeInterpreter;

std::vector<IntcodeNumberType> boostKeycodeProduced(const std::vector<IntcodeNumberType>& intcodeProgram, int input)
{
    IntcodeInterpreter ie{intcodeProgram};
    ie.addInput(input);

    ie.execute();

    return ie.getOutputs();
}

}
}
}
