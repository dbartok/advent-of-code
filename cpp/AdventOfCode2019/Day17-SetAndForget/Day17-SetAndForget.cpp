#include "Day17-SetAndForget.h"

#include "ScaffoldAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
size_t CHARACTER_LIMIT = 20;
}

namespace AdventOfCode
{
namespace Year2019
{
namespace Day17
{

using AdventOfCode::Year2019::Day05::IntcodeInterpreter;

Direction createDirection(char c)
{
    switch (c)
    {
        case '^':
            return Direction::UP;
        case 'v':
            return Direction::DOWN;
        case '<':
            return Direction::LEFT;
        case '>':
            return Direction::RIGHT;
    }

    throw std::runtime_error("Unknown direction: " + std::string{c});
}

RobotCameraView createRobotCameraView(const std::vector<IntcodeNumberType>& outputs)
{
    RobotCameraView robotCameraView;

    int i = 0;
    int j = 0;
    for (auto output : outputs)
    {
        if (output == '\n')
        {
            i = 0;
            ++j;
            continue;
        }

        if (output != '.')
        {
            robotCameraView.scaffolds.insert({i, j});
            if (output != '#')
            {
                robotCameraView.robotPosition = {i, j};
                robotCameraView.robotDirection = createDirection(output);
            }
        }
        ++i;
    }

    return robotCameraView;
}

bool getSubstringDecomposition(const std::string& stringToDecompose, size_t numSubstrings, std::vector<std::string>& result)
{
    if (numSubstrings == 0)
    {
        return stringToDecompose.empty();
    }

    for (size_t i = 1; i <= stringToDecompose.length() && i <= CHARACTER_LIMIT; ++i)
    {
        std::string prefix = stringToDecompose.substr(0, i);

        std::string remaining = std::regex_replace(stringToDecompose, std::regex(prefix), "");

        result.push_back(prefix);
        if (getSubstringDecomposition(remaining, numSubstrings - 1, result))
        {
            return true;
        }
        result.pop_back();
    }

    return false;
}

std::vector<std::string> getSubstringDecomposition(const std::string& s, size_t numSubstrings)
{
    std::vector<std::string> substrings;
    getSubstringDecomposition(s, numSubstrings, substrings);
    return substrings;
}

std::string createProgramInput(const std::vector<std::string>& steps)
{
    std::string stepsString = boost::join(steps, ",");
    std::string decomposableString = stepsString + ",";
    std::vector<std::string> decomposition;
    decomposition = getSubstringDecomposition(decomposableString, 3);

    for (auto& element : decomposition)
    {
        element = element.substr(0, element.size() - 1); // strip the trailing comma
    }

    std::string mainRoutine = std::regex_replace(stepsString, std::regex(decomposition.at(0)), "A");
    mainRoutine = std::regex_replace(mainRoutine, std::regex(decomposition.at(1)), "B");
    mainRoutine = std::regex_replace(mainRoutine, std::regex(decomposition.at(2)), "C");

    return mainRoutine + "\n" +
        decomposition.at(0) + "\n" +
        decomposition.at(1) + "\n" +
        decomposition.at(2) + "\n" +
        "n\n"; // turn off video feed
}

int sumOfAlignmentParameters(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreter{intcodeProgram};
    interpreter.execute();

    RobotCameraView cameraView = createRobotCameraView(interpreter.getOutputs());

    ScaffoldAnalyzer analyzer{std::move(cameraView)};

    return analyzer.getSumOfAlignmentParameters();
}

int dustCollectedByRobot(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreterForAnalysis{intcodeProgram};
    interpreterForAnalysis.execute();

    RobotCameraView cameraView = createRobotCameraView(interpreterForAnalysis.getOutputs());

    ScaffoldAnalyzer analyzer{std::move(cameraView)};

    analyzer.traverse();

    auto interactiveProgram{intcodeProgram};
    interactiveProgram.at(0) = 2;

    IntcodeInterpreter interpreterForMovingRobot{std::move(interactiveProgram)};

    std::string programInput = createProgramInput(analyzer.getJourneySteps());
    for (auto c : programInput)
    {
        interpreterForMovingRobot.addInput(c);
    }

    interpreterForMovingRobot.execute();
    return interpreterForMovingRobot.getOutputs().back();
}


}
}
}
