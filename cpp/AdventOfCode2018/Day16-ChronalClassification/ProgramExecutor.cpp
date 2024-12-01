#include "ProgramExecutor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day16
{

ProgramExecutor::ProgramExecutor(std::vector<Instruction> instructions, OpcodeToOpcodeString opcodeToOpcodeString)
    : m_instructions{std::move(instructions)}
    , m_opcodeToOpcodeString{std::move(opcodeToOpcodeString)}
    , m_registers{}
{

}

void ProgramExecutor::execute()
{
    for (const auto& instruction : m_instructions)
    {
        InstructionEvaluator instructionEvaluator{instruction, std::move(m_registers)};

        std::string opcodeString = m_opcodeToOpcodeString.at(instruction.opcode);
        m_registers = instructionEvaluator.evaluateAs(opcodeString);
    }
}

unsigned ProgramExecutor::getValueInFirstRegister() const
{
    return m_registers.front();
}

}
}
}
