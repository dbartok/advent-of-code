#include "Day24-ImmuneSystemSimulator.h"

#include "UnitGroupsParser.h"
#include "ImmuneFightSimulator.h"

#include <AdventOfCodeCommon/Utils.h>
#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day24
{

unsigned numUnitsOfWinningArmy(const std::vector<std::string>& armiesLines)
{
    UnitGroupsParser unitGroupsParser(armiesLines);
    unitGroupsParser.parse();

    ImmuneFightSimulator immuneFightSimulator{unitGroupsParser.getUnitGroups()};
    immuneFightSimulator.run();

    return immuneFightSimulator.getTotalRemainingNumUnits();
}

unsigned numUnitsImmuneSystemSmallestBoost(const std::vector<std::string>& armiesLines)
{
    int immuneSystemBoost = 0;
    while (true)
    {
        UnitGroupsParser unitGroupsParser(armiesLines, immuneSystemBoost++);
        unitGroupsParser.parse();

        ImmuneFightSimulator immuneFightSimulator{unitGroupsParser.getUnitGroups()};
        immuneFightSimulator.run();

        if (immuneFightSimulator.isThereRemainingFrom(Faction::INFECTION))
        {
            continue;
        }

        return immuneFightSimulator.getTotalRemainingNumUnits();
    }
}

}
}
}
