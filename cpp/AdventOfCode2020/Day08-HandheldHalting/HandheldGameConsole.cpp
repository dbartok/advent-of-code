#include "HandheldGameConsole.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day08
{

const char* ACC = "acc";
const char* JMP = "jmp";
const char* NOP = "nop";

HandheldGameConsole::HandheldGameConsole(std::vector<Instruction> instructions)
    : m_instructions{std::move(instructions)}
    , m_accumulator{0}
    , m_instructionPointer{0}
{

}

void HandheldGameConsole::runUntilRepeatedOrTerminates()
{
    std::unordered_set<int> instructionsExecuted;

    while (true)
    {
        if (isTerminated())
        {
            return;
        }

        bool wasInserted = instructionsExecuted.insert(m_instructionPointer).second;
        if (!wasInserted)
        {
            break;
        }

        executeCurrentInstruction();
    }
}

bool HandheldGameConsole::isTerminated() const
{
    return m_instructionPointer == m_instructions.size();
}

int HandheldGameConsole::getAccumulator() const
{
    return m_accumulator;
}

void HandheldGameConsole::executeCurrentInstruction()
{
    const auto& currentInstruction = m_instructions.at(m_instructionPointer);

    if (currentInstruction.name == JMP)
    {
        m_instructionPointer += (currentInstruction.arg - 1);
    }
    else if (currentInstruction.name == ACC)
    {
        m_accumulator += currentInstruction.arg;
    }

    ++m_instructionPointer;
}

}
}
}
