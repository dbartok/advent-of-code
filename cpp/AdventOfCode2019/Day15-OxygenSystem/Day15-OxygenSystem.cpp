#include "Day15-OxygenSystem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day15
{

int fewestNumberOfMovementsToOxygen(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreter{intcodeProgram};

    OxygenRepairDroid droid{std::move(interpreter)};

    droid.traverse();

    return droid.getDistanceToOxygen();
}

int numMinutesUntilOxygenSpreads(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreter{intcodeProgram};

    OxygenRepairDroid droid{std::move(interpreter)};

    droid.moveToOxygen();
    droid.traverse();

    return droid.getMaxDistance();
}

}
}
}
