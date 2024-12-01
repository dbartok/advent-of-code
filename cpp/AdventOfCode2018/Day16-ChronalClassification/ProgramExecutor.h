#pragma once

#include "InstructionEvaluator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day16
{

class ProgramExecutor
{
public:
    ProgramExecutor(std::vector<Instruction> instructions, OpcodeToOpcodeString opcodeToOpcodeString);

    void execute();

    unsigned getValueInFirstRegister() const;

private:
    std::vector<Instruction> m_instructions;
    OpcodeToOpcodeString m_opcodeToOpcodeString;

    Registers m_registers;
};

}
}
}
