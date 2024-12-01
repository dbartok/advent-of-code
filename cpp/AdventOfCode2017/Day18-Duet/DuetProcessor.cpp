#include "DuetProcessor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day18
{

DuetProcessor::DuetProcessor(AssemblyProgram assemblyProgram)
    : m_program0{assemblyProgram}              // Copy into first program
    , m_program1{std::move(assemblyProgram)}   // Move into second program
{
    m_program0.initializeProgramID(0);
    m_program1.initializeProgramID(1);

    DuetMessageQueue::SharedPtr messageQueueSharedPtr = std::make_shared<DuetMessageQueue>();

    m_program0.initMessageQueue(messageQueueSharedPtr);
    m_program1.initMessageQueue(std::move(messageQueueSharedPtr));
}

void DuetProcessor::run()
{
    while (true)
    {
        if (m_program0.getExecutionState() != ExecutionState::TERMINATED)
        {
            m_program0.runUntilHalts();
        }

        if (m_program1.getExecutionState() != ExecutionState::TERMINATED)
        {
            m_program1.runUntilHalts();
        }

        const ExecutionState program0ExecutionState = m_program0.getExecutionState();
        const ExecutionState program1ExecutionState = m_program1.getExecutionState();

        if ((program0ExecutionState == ExecutionState::UNABLE_TO_PROGRESS || program0ExecutionState == ExecutionState::TERMINATED) &&
            (program1ExecutionState == ExecutionState::UNABLE_TO_PROGRESS || program1ExecutionState == ExecutionState::TERMINATED))
        {
            break;
        }
    }
}

unsigned DuetProcessor::numTimesProgram1Sent() noexcept
{
    return m_program1.getNumTimesSent();
}

}
}
}
