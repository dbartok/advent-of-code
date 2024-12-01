#include "Day02-Dive.h"

#include "Submarine.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day02
{

Direction parseDirection(const std::string& directionString)
{
    if (directionString == "up")
    {
        return Direction::UP;
    }
    else if (directionString == "down")
    {
        return Direction::DOWN;
    }
    else if (directionString == "forward")
    {
        return Direction::FORWARD;
    }
    else
    {
        throw std::runtime_error("Invalid direction string: " + directionString);
    }
}

Instruction parseInstruction(const std::string& instructionLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, instructionLine, boost::is_any_of(" "));

    const Direction direction = parseDirection(tokens.at(0));
    const int length = std::stoi(tokens.at(1));

    return Instruction{direction, length};
}

std::vector<Instruction> parseInstructions(std::vector<std::string> instructionLines)
{
    std::vector<Instruction> instructions;

    for (const auto& line : instructionLines)
    {
        Instruction instruction = parseInstruction(line);
        instructions.push_back(std::move(instruction));
    }

    return instructions;
}

int finalHorizontalPositionAndDepthMultiplied(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions = parseInstructions(instructionLines);
    SimpleCourseSubmarine submarine{instructions};
    submarine.moveToFinalPosition();
    return submarine.getHorizontalPositionAndDepthMultiplied();
}

int finalHorizontalPositionAndDepthMultipliedWithAdjustedCourse(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions = parseInstructions(instructionLines);
    AdjustedCourseSubmarine submarine{instructions};
    submarine.moveToFinalPosition();
    return submarine.getHorizontalPositionAndDepthMultiplied();
}

}
}
}