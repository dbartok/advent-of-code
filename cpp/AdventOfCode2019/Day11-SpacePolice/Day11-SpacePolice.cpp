#include "Day11-SpacePolice.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day11
{

unsigned numPanelsPaintedAtLeastOnce(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreter{intcodeProgram};

    HullPaintingRobot robot{std::move(interpreter)};

    robot.paint();

    return robot.getNumPanelsPaintedAtLeastOnce();
}

std::string registrationIdentifier(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreter{intcodeProgram};
    CoordinatesToColor initialCoordinatesToColor;
    initialCoordinatesToColor[{0, 0}] = PaintColor::WHITE;

    HullPaintingRobot robot{std::move(interpreter), initialCoordinatesToColor};

    robot.paint();

    return robot.getRegistrationIdentifier();
}

}
}
}
