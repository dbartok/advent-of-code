#include "AssemblyProgram.h"

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

AssemblyProgram::AssemblyProgram(std::vector<AssemblyInstruction::SharedPtr> instructions) noexcept
    : m_instructions{std::move(instructions)}
    , m_state{}
{

}

void AssemblyProgram::runUntilHalts()
{
    if (m_state.getExecutionState() == ExecutionState::TERMINATED)
    {
        throw std::runtime_error("Trying to resume terminated program.");
    }

    m_state.executionState() = ExecutionState::RUNNING;

    unsigned numExecuted = 0;
    while (m_state.getExecutionState() != ExecutionState::TERMINATED)
    {
        auto currentInstruction = m_instructions[m_state.instructionIndex()];

        currentInstruction->execute(m_state);

        if (m_state.getExecutionState() == ExecutionState::BLOCKED)
        {
            if (numExecuted == 0)
            {
                m_state.executionState() = ExecutionState::UNABLE_TO_PROGRESS;
            }
            break;
        }

        if (currentInstruction->increasesInstructionIndex())
        {
            ++m_state.instructionIndex();
        }

        ++numExecuted;

        if (m_state.instructionIndex() < 0 || m_state.instructionIndex() >= m_instructions.size())
        {
            m_state.executionState() = ExecutionState::TERMINATED;
        }
    }

    assert(m_state.getExecutionState() != ExecutionState::RUNNING);
}

ExecutionState AssemblyProgram::getExecutionState() const noexcept
{
    return m_state.getExecutionState();
}

void AssemblyProgram::initializeProgramID(unsigned programID)
{
    if (programID > 1)
    {
        throw std::runtime_error("Only programIDs 0 and 1 are supported.");
    }

    m_state.initalizeProgramID(programID);
    *m_state.getRegisterValueSharedPtr("p") = programID;
}

void AssemblyProgram::initMessageQueue(DuetMessageQueue::SharedPtr messageQueueSharedPtr) noexcept
{
    m_state.initMessageQueue(std::move(messageQueueSharedPtr));
}


RegisterValueType AssemblyProgram::lastRecoveredFrequency() const
{
    boost::optional<RegisterValueType> frequency = m_state.getLastPlayedFrequency();

    if (!frequency.is_initialized())
    {
        throw std::runtime_error("No frequency was recovered so far.");
    }

    return frequency.get();
}

unsigned AssemblyProgram::getNumTimesSent() const noexcept
{
    return m_state.getNumTimesSent();
}

unsigned AssemblyProgram::getNumTimesMultInvoked() const noexcept
{
    return m_state.getNumTimesMultInvoked();
}

}
}
}
