#include "Day19-GoWithTheFlow.h"

#include "ControlFlowExecutor.h"
#include "HandOptimizedProgram.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day19
{

DecodedInstruction parseDecodedInstruction(const std::string& decodedInstructionLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, decodedInstructionLine, boost::is_any_of(" "));

    unsigned a = boost::lexical_cast<unsigned>(tokens.at(1));
    unsigned b = boost::lexical_cast<unsigned>(tokens.at(2));
    unsigned c = boost::lexical_cast<unsigned>(tokens.at(3));

    // Always use 0 as the opcode, because the instruction is decoded
    Instruction instruction{0, a, b, c};

    return DecodedInstruction{tokens.at(0), std::move(instruction)};
}

ControlFlowExecutor parseControlFlowExecutor(const std::vector<std::string>& programLines)
{
    std::vector<std::string> tokens;
    boost::split(tokens, programLines.at(0), boost::is_any_of(" "));
    unsigned instructionPtrRegister = boost::lexical_cast<unsigned>(tokens.at(1));

    std::vector<DecodedInstruction> decodedInstructions;
    for (size_t i = 1; i < programLines.size(); ++i)
    {
        decodedInstructions.push_back(parseDecodedInstruction(programLines.at(i)));
    }

    return ControlFlowExecutor{instructionPtrRegister, decodedInstructions};
}

unsigned valueInFirstRegisterAfterProcessHalts(const std::vector<std::string>& programLines)
{
    ControlFlowExecutor controlFlowExecutor = parseControlFlowExecutor(programLines);
    controlFlowExecutor.run();

    return controlFlowExecutor.getValueInFirstRegister();
}

unsigned valueInFirstRegisterAfterNewProcessHalts()
{
    return finalValueOfRegister0_v5();
}

}
}
}
