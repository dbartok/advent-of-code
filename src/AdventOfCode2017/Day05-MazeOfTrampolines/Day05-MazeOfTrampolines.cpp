#include "Day05-MazeOfTrampolines.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <functional>
END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

unsigned stepsWithInstructionModifierFunc(std::vector<int> instructions, std::function<void(int&)> modifierFunc)
{
    int position = 0;
    unsigned steps = 0;
    while (position >= 0 && position < instructions.size())
    {
        int newPosition = position + instructions[position];
        modifierFunc(instructions[position]);

        position = newPosition;
        ++steps;
    }

    return steps;
}

unsigned stepsInstructionsIncreasing(const std::vector<int>& instructions)
{
    return stepsWithInstructionModifierFunc(instructions, [](int& i) { ++i; });
}

unsigned stepsInstructionsIncreasingDecreasing(const std::vector<int>& instructions)
{
    return stepsWithInstructionModifierFunc(instructions, [](int& i) { i >= 3 ? --i : ++i; });
}

}
