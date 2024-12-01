#include "Day23-CoprocessorConflagration.h"

#include <AdventOfCode2017/Day18-Duet/AssemblyProgram.h>
#include <AdventOfCode2017/Day18-Duet/AssemblyProgramParser.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day23
{

using AdventOfCode::Year2017::Day18::AssemblyProgram;
using AdventOfCode::Year2017::Day18::AssemblyProgramParser;

unsigned numTimesMultInvoked(const std::vector<std::string>& instructionStrings)
{
    AssemblyProgramParser parser{instructionStrings};
    AssemblyProgram program = parser.createProgram();

    program.runUntilHalts();

    return program.getNumTimesMultInvoked();
}

unsigned overheatFinalValueOfH() noexcept
{
    return optimizedFinalValueOfH();
}

}
}
}
