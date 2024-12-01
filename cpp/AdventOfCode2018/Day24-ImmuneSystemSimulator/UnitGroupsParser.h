#pragma once

#include "UnitGroup.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day24
{

class UnitGroupsParser
{
public:
    UnitGroupsParser(std::vector<std::string> armiesLines, int immuneSystemBoost);
    UnitGroupsParser(std::vector<std::string> armiesLines);

    void parse();

    std::vector<UnitGroup> getUnitGroups() const;

private:
    std::vector<std::string> m_armiesLines;
    int m_immuneSystemBoost;

    size_t m_nextLineIndex = 1;
    Faction m_currentFaction = Faction::IMMUNE_SYSTEM;

    std::vector<UnitGroup> m_unitGroups;

    void parseArmyLine(const std::string& armyLine);
    DamageTypes parseDamageTypes(const std::string& armyLine, const std::string& name);
};

}
}
}
