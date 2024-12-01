#include "AmplifierChain.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day07
{

using AdventOfCode::Year2019::Day05::IntcodeProgramExecutionState;

AmplifierChain::AmplifierChain(const std::vector<IntcodeNumberType>& intcodeProgram, const std::vector<int>& phaseSettings)
{
    for (size_t i = 0; i < phaseSettings.size(); ++i)
    {
        IntcodeInterpreter amplifier{intcodeProgram};
        amplifier.addInput(phaseSettings.at(i));

        m_amplifiers.push_back(std::move(amplifier));
    }
}

void AmplifierChain::execute(int initialInput)
{
    for (size_t i = 0; i < m_amplifiers.size(); ++i)
    {
        m_amplifiers.at(i).addInput(initialInput);
        m_amplifiers.at(i).execute();
        initialInput = m_amplifiers.at(i).getOutputs().back();
    }
}

void AmplifierChain::executeWithFeedbackLoop(int initialInput)
{
    while (m_amplifiers.front().getExecutionState() != IntcodeProgramExecutionState::TERMINATED)
    {
        execute(initialInput);
        initialInput = getLastOutput();
    }
}

int AmplifierChain::getLastOutput() const
{
    return m_amplifiers.back().getOutputs().back();
}

}
}
}
