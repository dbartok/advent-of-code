#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
#include <unordered_set>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day24
{

using DamageType = std::string;
using DamageTypes = std::unordered_set<std::string>;

enum class Faction
{
    IMMUNE_SYSTEM,
    INFECTION,
};

using UnitGroupIDType = int;

class UnitGroup
{
public:
    UnitGroup(
        Faction faction,
        int numUnits,
        int hitPoints,
        DamageTypes weaknesses,
        DamageTypes immunities,
        int attackDamage,
        DamageType attackType,
        int initiative)
        : m_faction{faction}
        , m_numUnits{numUnits}
        , m_hitPoints{hitPoints}
        , m_weaknesses{std::move(weaknesses)}
        , m_immunities{std::move(immunities)}
        , m_attackDamage{attackDamage}
        , m_attackType{std::move(attackType)}
        , m_initiative{initiative}
    {

    }

    bool operator==(const UnitGroup& other) const
    {
        return
            m_faction == other.m_faction &&
            m_numUnits == other.m_numUnits &&
            m_hitPoints == other.m_hitPoints &&
            m_weaknesses == other.m_weaknesses &&
            m_immunities == other.m_immunities &&
            m_attackDamage == other.m_attackDamage &&
            m_attackType == other.m_attackType &&
            m_initiative == other.m_initiative;
    }

    int getInitiative() const
    {
        return m_initiative;
    }

    UnitGroupIDType getID() const
    {
        // initiative is also a unique ID
        return m_initiative;
    }

    int getNumUnits() const
    {
        return m_numUnits;
    }

    Faction getFaction() const
    {
        return m_faction;
    }

    int getEffectivePower() const
    {
        return m_numUnits * m_attackDamage;
    }

    bool isHostileTowards(const UnitGroup& other) const
    {
        return m_faction != other.m_faction;
    }

    bool canDealDamageTo(const UnitGroup& target) const
    {
        return target.m_immunities.find(m_attackType) == target.m_immunities.end();
    }

    int numPossibleDamageTo(const UnitGroup& target) const
    {
        if (!canDealDamageTo(target))
        {
            throw std::runtime_error("Cannot calculate possible damage because target is immune.");
        }

        int damage = getEffectivePower();

        if (target.m_weaknesses.find(m_attackType) != target.m_weaknesses.end())
        {
            damage *= 2;
        }

        return damage;
    }

    bool isEmpty() const
    {
        return m_numUnits <= 0;
    }

    void attack(UnitGroup& target) const
    {
        int damage = numPossibleDamageTo(target);
        int killedUnits = damage / target.m_hitPoints;
        target.m_numUnits -= killedUnits;
    }

private:
    Faction m_faction;
    int m_numUnits;
    int m_hitPoints;
    DamageTypes m_weaknesses;
    DamageTypes m_immunities;
    int m_attackDamage;
    DamageType m_attackType;
    int m_initiative;
};

}
}
}
