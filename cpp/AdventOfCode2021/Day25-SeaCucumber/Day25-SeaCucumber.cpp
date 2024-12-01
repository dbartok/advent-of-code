#include "Day25-SeaCucumber.h"

#include "SeaCucumberMovementSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day25
{

unsigned firstStepWithoutAnyMovement(const std::vector<std::string>& seaCucumberInitialPositionsLines)
{
    SeaCucumberMovementSimulator simulator{seaCucumberInitialPositionsLines};
    simulator.simulateUntilFirstStepWithoutAnyMovement();
    return simulator.getNumSteps();
}

}
}
}