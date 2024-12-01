#include "ControlFlowExecutor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day19
{

using AdventOfCode::Year2018::Day16::InstructionEvaluator;

ControlFlowExecutor::ControlFlowExecutor(unsigned instructionPtrRegister, std::vector<DecodedInstruction> decodedInstructions)
    : m_instructionPtrRegister{instructionPtrRegister}
    , m_decodedInstructions(decodedInstructions)
    , m_registers{}
{

}

void ControlFlowExecutor::run()
{
    while (true)
    {
        unsigned instructionPointer = m_registers.at(m_instructionPtrRegister);

        if (instructionPointer >= m_decodedInstructions.size())
        {
            break;
        }

        const auto& decodedInstruction = m_decodedInstructions.at(instructionPointer);

        InstructionEvaluator instructionEvaluator{decodedInstruction.instruction, std::move(m_registers)};
        m_registers = instructionEvaluator.evaluateAs(decodedInstruction.opcodeString);
        ++m_registers.at(m_instructionPtrRegister);
    }
}

unsigned ControlFlowExecutor::getValueInFirstRegister() const
{
    return m_registers.front();
}

}
}
}
