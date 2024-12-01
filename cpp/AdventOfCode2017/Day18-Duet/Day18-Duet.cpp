#include "Day18-Duet.h"

#include "DuetProcessor.h"
#include "AssemblyProgramParser.h"
#include "AssemblyProgram.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day18
{

RegisterValueType valueOfFirstRecoveredFrequency(const std::vector<std::string>& instructionStrings)
{
    SoundProgramParser parser{instructionStrings};
    AssemblyProgram program = parser.createProgram();

    program.runUntilHalts();

    return program.lastRecoveredFrequency();
}

unsigned numTimesProgram1Sent(const std::vector<std::string>& instructionStrings)
{
    MessageQueueProgramParser parser{instructionStrings};
    AssemblyProgram program = parser.createProgram();

    DuetProcessor duetProcessor{program};

    duetProcessor.run();

    return duetProcessor.numTimesProgram1Sent();
}

}
}
}
