#include "Day18-LavaductLagoon.h"

#include "DigPlanAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day18
{

Vector2D parseDirectionChar(const char directionChar)
{
    if (directionChar == 'U' || directionChar == '3')
    {
        return {0, -1};
    }
    else if (directionChar == 'D' || directionChar == '1')
    {
        return {0, 1};
    }
    else if (directionChar == 'L' || directionChar == '2')
    {
        return {-1, 0};
    }
    else if (directionChar == 'R' || directionChar == '0')
    {
        return {1, 0};
    }

    throw std::runtime_error("Invalid direction char: " + std::string{directionChar});
}

Instruction parseDigPlanLine(const std::string& digPlanLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, digPlanLine, boost::is_any_of(" "));

    Vector2D direction = parseDirectionChar(tokens.at(0).front());
    const int numTiles = std::stoi(tokens.at(1));

    return {std::move(direction), numTiles};
}

Instruction parseDigPlanLineWithSwappedInstructions(const std::string& digPlanLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, digPlanLine, boost::is_any_of(" "));

    const std::string hexString = tokens.back().substr(2, 6);
    const char directionChar = hexString.back();
    const std::string numTilesString = hexString.substr(0, hexString.size() - 1);

    Vector2D direction = parseDirectionChar(directionChar);
    const int numTiles = std::stoi(numTilesString, nullptr, 16);

    return {std::move(direction), numTiles};
}

std::vector<Instruction> parseDigPlanLines(const std::vector<std::string>& digPlanLines)
{
    std::vector<Instruction> instructions;

    for (const auto& digPlanLine : digPlanLines)
    {
        Instruction instruction = parseDigPlanLine(digPlanLine);
        instructions.push_back(std::move(instruction));
    }

    return instructions;
}

std::vector<Instruction> parseDigPlanLinesWithSwappedInstructions(const std::vector<std::string>& digPlanLines)
{
    std::vector<Instruction> instructions;

    for (const auto& digPlanLine : digPlanLines)
    {
        Instruction instruction = parseDigPlanLineWithSwappedInstructions(digPlanLine);
        instructions.push_back(std::move(instruction));
    }

    return instructions;
}

int64_t amountOfLavaHeld(const std::vector<std::string>& digPlanLines)
{
    std::vector<Instruction> instructions = parseDigPlanLines(digPlanLines);

    DigPlanAnalyzer digPlanAnalyzer{std::move(instructions)};

    return digPlanAnalyzer.getAmountOfLavaHeld();
}

int64_t amountOfLavaHeldWithSwappedInstructions(const std::vector<std::string>& digPlanLines)
{
    std::vector<Instruction> instructions = parseDigPlanLinesWithSwappedInstructions(digPlanLines);

    DigPlanAnalyzer digPlanAnalyzer{std::move(instructions)};

    return digPlanAnalyzer.getAmountOfLavaHeld();
}

}
}
}