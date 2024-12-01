#include "UnitGroupsParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day24
{

UnitGroupsParser::UnitGroupsParser(std::vector<std::string> armiesLines, int immuneSystemBoost)
    : m_armiesLines{std::move(armiesLines)}
    , m_immuneSystemBoost{immuneSystemBoost}
{

}

UnitGroupsParser::UnitGroupsParser(std::vector<std::string> armiesLines)
    : UnitGroupsParser(std::move(armiesLines), 0)
{

}

void UnitGroupsParser::parse()
{
    while (m_nextLineIndex < m_armiesLines.size())
    {
        std::string currentLine = m_armiesLines[m_nextLineIndex++];

        if (currentLine.empty())
        {
            m_currentFaction = Faction::INFECTION;
            ++m_nextLineIndex;
        }
        else
        {
            parseArmyLine(currentLine);
        }
    }
}

std::vector<UnitGroup> UnitGroupsParser::getUnitGroups() const
{
    return m_unitGroups;
}

void UnitGroupsParser::parseArmyLine(const std::string& armyLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, armyLine, boost::is_any_of(" "));
    int numUnits = std::stoi(tokens[0]);
    int hitPoints = std::stoi(tokens[4]);
    DamageTypes weaknesses = parseDamageTypes(armyLine, "weak");
    DamageTypes immunities = parseDamageTypes(armyLine, "immune");
    int attackDamage = std::stoi(*(tokens.crbegin() + 5));
    DamageType attackType = *(tokens.crbegin() + 4);
    int initiative = std::stoi(*tokens.crbegin());

    if (m_currentFaction == Faction::IMMUNE_SYSTEM)
    {
        attackDamage += m_immuneSystemBoost;
    }

    m_unitGroups.emplace_back(m_currentFaction, numUnits, hitPoints, weaknesses, immunities, attackDamage, attackType, initiative);
}

DamageTypes UnitGroupsParser::parseDamageTypes(const std::string& armyLine, const std::string& name)
{
    std::regex damageTypeRegex(name + R"( to ((?:[a-z]+(?:, )?)+)[;\)])");
    std::smatch matchResults;
    std::regex_search(armyLine, matchResults, damageTypeRegex);

    if (matchResults.size() == 0)
    {
        return {};
    }

    std::string damageTypesString = matchResults[1];
    DamageTypes damageTypes;
    boost::split(damageTypes, damageTypesString, boost::is_any_of(" ,"), boost::token_compress_on);

    return damageTypes;
}

}
}
}
