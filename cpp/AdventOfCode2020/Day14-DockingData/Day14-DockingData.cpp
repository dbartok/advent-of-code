#include "Day14-DockingData.h"

#include "BitmaskProgramExecutor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day14
{

Instruction parseInstruction(const std::string& instruction)
{
    std::vector<std::string> tokens;
    if (instruction.substr(0, 3) == "mem")
    {
        boost::split(tokens, instruction, boost::is_any_of("[]= "), boost::token_compress_on);
        return Instruction{InstructionType::MEM, tokens.at(2), std::stoull(tokens.at(1))};
    }
    else
    {
        boost::split(tokens, instruction, boost::is_any_of("= "), boost::token_compress_on);
        return Instruction{InstructionType::MASK, tokens.at(1)};
    }
}

std::vector<Instruction> parseInstructions(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions;

    for (const auto& line : instructionLines)
    {
        Instruction instruction = parseInstruction(line);
        instructions.push_back(std::move(instruction));
    }

    return instructions;
}

uint64_t sumOfValuesInMemoryAfterCompletion(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions = parseInstructions(instructionLines);
    BitmaskProgramExecutor bitmaskProgramExecutor{std::move(instructions)};
    bitmaskProgramExecutor.execute();
    return bitmaskProgramExecutor.getSumOfValuesInMemory();
}

uint64_t sumOfValuesInMemoryAfterDecoderCompletion(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions = parseInstructions(instructionLines);
    BitmaskDecoderProgramExecutor bitmaskDecoderProgramExecutor{std::move(instructions)};
    bitmaskDecoderProgramExecutor.execute();
    return bitmaskDecoderProgramExecutor.getSumOfValuesInMemory();
}

}
}
}
