#include "Day10-CathodeRayTube.h"

#include "CommunicationDevice.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned ADDX_INSTRUCTION_DURATION = 2;
const unsigned NOOP_INSTRUCTION_DURATION = 1;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day10
{

Instruction parseInstructionLine(const std::string& instructionLine)
{
    std::vector<std::string> tokens;
    boost:split(tokens, instructionLine, boost::is_any_of(" "));

    if (tokens.at(0) == "addx")
    {
        return Instruction{std::stoi(tokens.at(1)), ADDX_INSTRUCTION_DURATION};
    }
    else
    {
        return Instruction{0, NOOP_INSTRUCTION_DURATION};
    }
}

std::vector<Instruction> parseInstructionLines(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions;

    for (const auto& instructionLine : instructionLines)
    {
        Instruction instruction = parseInstructionLine(instructionLine);
        instructions.push_back(std::move(instruction));
    }

    return instructions;
}

int sumOfInterestingSignalStrengths(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions = parseInstructionLines(instructionLines);

    CommunicationDevice communicationDevice{std::move(instructions)};

    communicationDevice.runProgram();

    return communicationDevice.getSumOfInterestingSignalStrengths();
}

std::string imageAppearingOnScreen(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions = parseInstructionLines(instructionLines);

    CommunicationDevice communicationDevice{std::move(instructions)};

    communicationDevice.runProgram();

    return communicationDevice.getImageAppearingOnScreen();
}

}
}
}