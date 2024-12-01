#pragma once

#include "AdventOfCode2018/Day16-ChronalClassification/InstructionEvaluator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day19
{

using AdventOfCode::Year2018::Day16::Instruction;
using AdventOfCode::Year2018::Day16::Registers;

struct DecodedInstruction
{
    std::string opcodeString;
    Instruction instruction;

    DecodedInstruction(std::string opcodeString, Instruction instruction)
        : opcodeString{std::move(opcodeString)}
        , instruction{std::move(instruction)}
    {

    }
};

class ControlFlowExecutor
{
public:
    ControlFlowExecutor(unsigned instructionPtrRegister, std::vector<DecodedInstruction> decodedInstructions);

    void run();

    unsigned getValueInFirstRegister() const;

private:
    unsigned m_instructionPtrRegister;
    std::vector<DecodedInstruction> m_decodedInstructions;

    Registers m_registers;
};

}
}
}
