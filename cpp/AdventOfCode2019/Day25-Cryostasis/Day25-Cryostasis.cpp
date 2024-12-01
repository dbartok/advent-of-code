#include "Day25-Cryostasis.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <array>
#include <sstream>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day25
{

std::array<std::string, 23> INPUTS =
{
    "south",
    "take mouse",
    "north",
    "west",
    "north",
    "north",
    "north",
    "west",
    "take semiconductor",
    "east",
    "south",
    "west",
    "south",
    "take hypercube",
    "north",
    "east",
    "south",
    "west",
    "take antenna",
    "west",
    "south",
    "south",
    "south",
};

std::string passwordForMainAirlock(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreter{intcodeProgram};

    std::string inputString;
    for (auto& instruction : INPUTS)
    {
        inputString += (instruction + '\n');
    }

    std::istringstream iss(inputString);

    IntcodeTextAdventure textAdventure{interpreter, iss};

    textAdventure.play();

    return textAdventure.getPasscode();
}

}
}
}
