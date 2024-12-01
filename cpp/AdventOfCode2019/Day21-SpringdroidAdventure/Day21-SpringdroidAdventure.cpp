#include "Day21-SpringdroidAdventure.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <array>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day21
{

using AdventOfCode::Year2019::Day05::IntcodeInterpreter;

using SpringScriptProgram = std::array<std::string, 15>;

const SpringScriptProgram WALK_PROGRAM =
{
    "NOT A J", // Condition: hole at A
    "NOT B T",
    "OR T J", // or hole at B
    "NOT C T",
    "OR T J", // or hole at C
    "AND D J", // and ground at D.
    "WALK"
};

const SpringScriptProgram RUN_PROGRAM =
{
    "NOT A J", // Condition #1: hole at A
    "NOT B T",
    "OR T J", // or hole at B
    "NOT C T",
    "OR T J", // or hole at C
    "AND D J", // and ground at D.
    "NOT E T",
    "NOT T T", // Condition #2: ground at E
    "OR H T", // or ground at H.
    "AND T J", // Condition #1 and Condition #2.
    "RUN"
};

std::string createSpringscriptInput(const SpringScriptProgram& program)
{
    std::string springscriptInput;
    for (auto& instruction : program)
    {
        if (!instruction.empty())
        {
            springscriptInput += (instruction + '\n');
        }
    }

    return springscriptInput;
}

IntcodeNumberType amountOfHullDamage(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreter{intcodeProgram};

    std::string inputString = createSpringscriptInput(WALK_PROGRAM);

    for (auto c : inputString)
    {
        interpreter.addInput(c);
    }

    interpreter.execute();

    return interpreter.getOutputs().back();
}

IntcodeNumberType amountOfHullDamageExtendedSensors(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreter{intcodeProgram};

    std::string inputString = createSpringscriptInput(RUN_PROGRAM);

    for (auto c : inputString)
    {
        interpreter.addInput(c);
    }

    interpreter.execute();

    return interpreter.getOutputs().back();
}

}
}
}
