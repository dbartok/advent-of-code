#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "Instruction.h"
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day08
{

class Processor
{
public:
    Processor(std::vector<Instruction> instructions);
    void run();
    int largestRegister() const;
    int globalMaxValueOfRegisters() const noexcept;

private:
    std::vector<Instruction> m_instructions;
    State m_state;
};

}
}
}
