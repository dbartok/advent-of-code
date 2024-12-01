#include "Day08-LikeRegisters.h"

#include "Processor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day08
{

int largestRegisterAfterCompletion(const std::vector<Instruction>& instructions)
{
    Processor processor{instructions};
    processor.run();
    return processor.largestRegister();
}

int largestRegisterDuringExecution(const std::vector<Instruction>& instructions)
{
    Processor processor{instructions};
    processor.run();
    return processor.globalMaxValueOfRegisters();
}

}
}
}
