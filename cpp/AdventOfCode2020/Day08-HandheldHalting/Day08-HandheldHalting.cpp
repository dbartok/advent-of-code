#include "Day08-HandheldHalting.h"

#include "HandheldGameConsole.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day08
{

Instruction parseInstruction(const std::string& instructionLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, instructionLine, boost::is_any_of(" "));

    std::string name = tokens.at(0);
    int arg = std::stoi(tokens.at(1));

    return Instruction{std::move(name), arg};
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

int valueInAccAfterFirstDuplicateInstruction(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions = parseInstructions(instructionLines);
    HandheldGameConsole handheldGameConsole{std::move(instructions)};
    handheldGameConsole.runUntilRepeatedOrTerminates();

    return handheldGameConsole.getAccumulator();
}

int valueInAccAfterRepairedProgramTerminates(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> originalInstructions = parseInstructions(instructionLines);

    for (size_t i = 0; i < originalInstructions.size(); ++i)
    {
        auto repairedInstructions{originalInstructions};
        auto& modifiedInstruction = repairedInstructions.at(i);
        if (modifiedInstruction.name == JMP)
        {
            modifiedInstruction.name = NOP;
        }
        else if (modifiedInstruction.name == NOP)
        {
            modifiedInstruction.name = JMP;
        }
        else
        {
            continue;
        }

        HandheldGameConsole handheldGameConsole{std::move(repairedInstructions)};
        handheldGameConsole.runUntilRepeatedOrTerminates();
        if (handheldGameConsole.isTerminated())
        {
            return handheldGameConsole.getAccumulator();
        }
    }

    throw std::runtime_error("Cannot repair the program.");
}

}
}
}
