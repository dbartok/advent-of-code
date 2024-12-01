#include "Day22-MonkeyMap.h"

#include "MonkeyMapPathfinder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day22
{

using MonkeyNoteTextSection = std::vector<std::string>;

MonkeyMap parseMonkeyMapLines(const std::vector<std::string>& monkeyMapLines)
{
    const auto longestLineIter = std::max_element(monkeyMapLines.cbegin(), monkeyMapLines.cend(), [](const auto& lhs, const auto& rhs)
                                                  {
                                                      return lhs.size() < rhs.size();
                                                  });
    const size_t longestLineSize = longestLineIter->size();

    MonkeyMap monkeyMap;

    std::transform(monkeyMapLines.cbegin(), monkeyMapLines.cend(), std::back_inserter(monkeyMap), [longestLineSize](const auto& line)
                   {
                       auto paddedLine{line};
                       if (line.size() < longestLineSize)
                       {
                           paddedLine.insert(paddedLine.end(), longestLineSize - line.size(), ' ');
                       }
                       return paddedLine;
                   });

    return monkeyMap;
}

Instructions parseInstructionLine(const std::string& instructionLine)
{
    Instructions instructions;
    Instruction currentInstruction;

    for (const char c : instructionLine)
    {
        if (isdigit(c))
        {
            currentInstruction.numSteps *= 10;
            currentInstruction.numSteps += c - '0';
        }
        else
        {
            currentInstruction.rotationDirection = c;
            instructions.push_back(std::move(currentInstruction));
            currentInstruction = {};
        }
    }

    instructions.push_back(std::move(currentInstruction));

    return instructions;
}

std::pair<MonkeyMap, Instructions> parseMonkeyNoteLines(const std::vector<std::string>& monkeyNoteLines)
{
    std::vector<MonkeyNoteTextSection> monkeyNoteTextSections;
    boost::split(monkeyNoteTextSections, monkeyNoteLines, [](const auto& elem) { return elem.empty(); });

    MonkeyMap monkeyMap = parseMonkeyMapLines(monkeyNoteTextSections.at(0));
    Instructions instructions = parseInstructionLine(monkeyNoteTextSections.at(1).front());

    return {std::move(monkeyMap), std::move(instructions)};
}

int finalPassword(const std::vector<std::string>& monkeyNoteLines)
{
    MonkeyMap monkeyMap;
    Instructions instructions;
    std::tie(monkeyMap, instructions) = parseMonkeyNoteLines(monkeyNoteLines);

    MonkeyMapPathfinder monkeyMapPathfinder{std::move(monkeyMap), std::move(instructions)};

    monkeyMapPathfinder.executeInstructions();

    return monkeyMapPathfinder.getFinalPassword();
}

int finalPasswordWithCubeMap(const std::vector<std::string>& monkeyNoteLines, unsigned cubeSize)
{
    MonkeyMap monkeyMap;
    Instructions instructions;
    std::tie(monkeyMap, instructions) = parseMonkeyNoteLines(monkeyNoteLines);

    MonkeyMapCubePathfinder monkeyMapCubePathfinder{std::move(monkeyMap), std::move(instructions), cubeSize};

    monkeyMapCubePathfinder.fold();

    monkeyMapCubePathfinder.executeInstructions();

    return monkeyMapCubePathfinder.getFinalPassword();
}

}
}
}