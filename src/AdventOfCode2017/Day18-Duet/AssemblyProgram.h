#pragma once

#include "AssemblyProgramState.h"
#include "AssemblyInstruction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

class AssemblyProgram
{
public:
    AssemblyProgram(std::vector<AssemblyInstruction::SharedPtr> instructions) noexcept;

    void runUntilHalts();
    ExecutionState getExecutionState() const noexcept;

    void initializeProgramID(unsigned programID);
    void initMessageQueue(DuetMessageQueue::SharedPtr messageQueueSharedPtr) noexcept;

    RegisterValueType lastRecoveredFrequency() const;
    unsigned getNumTimesSent() const noexcept;
    unsigned getNumTimesMultInvoked() const noexcept;

private:
    std::vector<AssemblyInstruction::SharedPtr> m_instructions;
    AssemblyProgramState m_state;
};

}
