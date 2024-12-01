#include "Day07-AmplificationCircuit.h"

#include "AmplifierChain.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const size_t NUM_AMPLIFIERS = 5;
const int SERIAL_FIRST_PHASE = 0;
const int FEEDBACK_LOOP_FIRST_PHASE = 5;
const int INITIAL_INPUT = 0;

}

namespace AdventOfCode
{
namespace Year2019
{
namespace Day07
{

enum class AmplifierLayout
{
    SERIAL,
    FEEDBACK_LOOP,
};

int highestPossibleSignalSent(const std::vector<IntcodeNumberType>& intcodeProgram, AmplifierLayout layout, int firstPhase)
{
    std::vector<int> phaseSettings(NUM_AMPLIFIERS);
    std::iota(phaseSettings.begin(), phaseSettings.end(), firstPhase);

    int maxOutput = std::numeric_limits<int>::min();

    while (true)
    {
        AmplifierChain amplifierChain{intcodeProgram, phaseSettings};
        if (layout == AmplifierLayout::SERIAL)
        {
            amplifierChain.execute(INITIAL_INPUT);
        }
        else if (layout == AmplifierLayout::FEEDBACK_LOOP)
        {
            amplifierChain.executeWithFeedbackLoop(INITIAL_INPUT);
        }

        maxOutput = std::max(maxOutput, amplifierChain.getLastOutput());

        if (!std::next_permutation(phaseSettings.begin(), phaseSettings.end()))
        {
            break;
        }
    }

    return maxOutput;
}

int highestPossibleSignalSent(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    return highestPossibleSignalSent(intcodeProgram, AmplifierLayout::SERIAL, SERIAL_FIRST_PHASE);
}

int highestPossibleSignalSentWithAmplification(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    return highestPossibleSignalSent(intcodeProgram, AmplifierLayout::FEEDBACK_LOOP, FEEDBACK_LOOP_FIRST_PHASE);
}

}
}
}
