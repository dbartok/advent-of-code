#include "Day02-ProgramAlarm.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day02
{

int getValueInPositionZeroAfterProgramHalts(std::vector<int> intcodeProgram, int noun, int verb)
{
    intcodeProgram.at(1) = noun;
    intcodeProgram.at(2) = verb;

    size_t index = 0;
    while (true)
    {
        const int code = intcodeProgram.at(index);
        if (code == 1 || code == 2)
        {
            const int operandOneIndex = intcodeProgram.at(index + 1);
            const int operandTwoIndex = intcodeProgram.at(index + 2);
            const int resultIndex = intcodeProgram.at(index + 3);

            const int operandOne = intcodeProgram.at(operandOneIndex);
            const int operandTwo = intcodeProgram.at(operandTwoIndex);
            int& result = intcodeProgram.at(resultIndex);
            if (code == 1)
            {
                result = operandOne + operandTwo;
            }
            else if (code == 2)
            {
                result = operandOne * operandTwo;
            }
        }
        else if (code == 99)
        {
            break;
        }

        index += 4;
    }
    return intcodeProgram.front();
}

int getScoreOfNounAndVerbForSpecificOutput(std::vector<int> intcodeProgram, int desiredOutput)
{
    for (int noun = 0; noun <= 99; ++noun)
    {
        for (int verb = 0; verb <= 99; ++verb)
        {
            try
            {
                const int output = getValueInPositionZeroAfterProgramHalts(intcodeProgram, noun, verb);

                if (output == desiredOutput)
                {
                    return 100 * noun + verb;
                }
            }
            catch (std::out_of_range)
            {
                continue;
            }
        }
    }

    throw std::runtime_error("No solution found");
}

}
}
}
