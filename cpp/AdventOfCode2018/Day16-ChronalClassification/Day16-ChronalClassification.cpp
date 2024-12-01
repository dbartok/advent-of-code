#include "Day16-ChronalClassification.h"

#include "OpcodeDiscovery.h"
#include "ProgramExecutor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/lexical_cast.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day16
{

std::vector<unsigned> parseAllNumbers(std::string line)
{
    std::vector<unsigned> allNumbers;

    std::regex numbersRegex("([0-9]+)");
    std::smatch matchResults;

    while (regex_search(line, matchResults, numbersRegex))
    {
        allNumbers.push_back(boost::lexical_cast<unsigned>(matchResults.str()));
        line = matchResults.suffix();
    }

    return allNumbers;
}

Instruction parseInstruction(const std::string& line)
{
    std::vector<unsigned> numbers = parseAllNumbers(line);

    if (numbers.size() != 4)
    {
        throw std::runtime_error("Unable to parse instruction: " + line);
    }

    return Instruction{numbers[0], numbers[1], numbers[2], numbers[3]};
}

Registers parseRegisters(const std::string& line)
{
    Registers registers{};

    std::vector<unsigned> numbers = parseAllNumbers(line);
    if (numbers.size() != 4)
    {
        throw std::runtime_error("Unable to parse registers: " + line);
    }

    std::copy(numbers.cbegin(), numbers.cend(), registers.begin());

    return registers;
}

std::vector<CapturedSample> parseCapturedSamples(const std::vector<std::string>& opcodeManualLines)
{
    std::vector<CapturedSample> capturedSamples;

    size_t lineIndex = 0;
    while (true)
    {
        if (opcodeManualLines[lineIndex].find("Before") == std::string::npos)
        {
            break;
        }

        Registers before = parseRegisters(opcodeManualLines[lineIndex]);
        Instruction instruction = parseInstruction(opcodeManualLines[lineIndex + 1]);
        Registers after = parseRegisters(opcodeManualLines[lineIndex + 2]);

        capturedSamples.emplace_back(std::move(before), std::move(instruction), std::move(after));

        lineIndex += 4;
    }

    return capturedSamples;

}

std::vector<Instruction> parseProgramInstructions(const std::vector<std::string>& opcodeManualLines)
{
    std::vector<Instruction> programInstructions;

    size_t lineIndex = 2;
    for (; lineIndex < opcodeManualLines.size(); ++lineIndex)
    {
        if (opcodeManualLines[lineIndex].empty() && opcodeManualLines[lineIndex - 1].empty() && opcodeManualLines[lineIndex - 2].empty())
        {
            ++lineIndex;
            break;
        }
    }

    for (; lineIndex < opcodeManualLines.size(); ++lineIndex)
    {
        Instruction instruction = parseInstruction(opcodeManualLines[lineIndex]);
        programInstructions.push_back(std::move(instruction));
    }

    return programInstructions;
}

unsigned numSamplesBehaveMoreThanThreeOpcodes(const std::vector<std::string>& opcodeManualLines)
{
    std::vector<CapturedSample> capturedSamples = parseCapturedSamples(opcodeManualLines);

    OpcodeDiscovery opcodeDiscovery{capturedSamples};
    opcodeDiscovery.discover();

    return opcodeDiscovery.getNumSamplesBehaveMoreThanThreeOpcodes();
}

unsigned valueInFirstRegisterAfterProgramFinishes(const std::vector<std::string>& opcodeManualLines)
{
    std::vector<CapturedSample> capturedSamples = parseCapturedSamples(opcodeManualLines);

    OpcodeDiscovery opcodeDiscovery{capturedSamples};
    opcodeDiscovery.discover();

    std::vector<Instruction> programInstructions = parseProgramInstructions(opcodeManualLines);

    ProgramExecutor programExecutor{std::move(programInstructions), opcodeDiscovery.getOpcodeToOpcodeString()};
    programExecutor.execute();

    return programExecutor.getValueInFirstRegister();
}

}
}
}
