#pragma once

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

class DuetProcessor
{
public:
    DuetProcessor(AssemblyProgram assemblyProgram);
    void run();
    unsigned numTimesProgram1Sent() noexcept;

private:
    AssemblyProgram m_program0;
    AssemblyProgram m_program1;
};

}
}
}
