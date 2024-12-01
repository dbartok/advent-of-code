#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day08
{

extern const char* ACC;
extern const char* JMP;
extern const char* NOP;

struct Instruction
{
    std::string name;
    int arg;
};

class HandheldGameConsole
{
public:
    HandheldGameConsole(std::vector<Instruction> instructions);

    void runUntilRepeatedOrTerminates();

    bool isTerminated() const;
    int getAccumulator() const;

private:
    std::vector<Instruction> m_instructions;

    int m_accumulator;
    int m_instructionPointer;

    void executeCurrentInstruction();
};

}
}
}
