#pragma once

#include <AdventOfCode2019/Day05-SunnyWithAsteroids/IntcodeInterpreter.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day07
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;
using AdventOfCode::Year2019::Day05::IntcodeInterpreter;

class AmplifierChain
{
public:
    AmplifierChain(const std::vector<IntcodeNumberType>& intcodeProgram, const std::vector<int>& phaseSettings);

    void execute(int initialInput);
    void executeWithFeedbackLoop(int initialInput);

    int getLastOutput() const;

private:
    std::vector<IntcodeInterpreter> m_amplifiers;
};

}
}
}
