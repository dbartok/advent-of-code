#include "IntcodeTextAdventure.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cassert>
#include <regex>
#include <string>
#include <sstream>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day25
{

using AdventOfCode::Year2019::Day05::IntcodeProgramExecutionState;

IntcodeTextAdventure::IntcodeTextAdventure(IntcodeInterpreter interpreter, std::istream& in)
    : m_interpreter{std::move(interpreter)}
    , m_in{in}
{

}

void IntcodeTextAdventure::play()
{
    while (m_interpreter.getExecutionState() != IntcodeProgramExecutionState::TERMINATED)
    {
        m_interpreter.clearOutputs();
        m_interpreter.execute();
        feedInput();
    }
}

std::string IntcodeTextAdventure::getPasscode()
{
    std::ostringstream oss;
    for (auto c : m_interpreter.getOutputs())
    {
        oss << static_cast<char>(c);
    }

    std::string outputString = oss.str();
    std::smatch match;
    std::regex numbersRegex("[0-9]+");
    std::regex_search(outputString, match, numbersRegex);

    assert(match.size() == 1);
    return match[0];
}

void IntcodeTextAdventure::feedInput()
{
    std::string inputString;
    std::getline(m_in, inputString);
    inputString += '\n';

    for (auto c : inputString)
    {
        m_interpreter.addInput(c);
    }
}

}
}
}
