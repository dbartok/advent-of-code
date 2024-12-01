#include "ImmuneFightSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day24
{

ImmuneFightSimulator::ImmuneFightSimulator(std::vector<UnitGroup> unitGroups)
    : m_unitGroupMap{}
{
    for (auto& unitGroup : unitGroups)
    {
        UnitGroupIDType unitGroupID = unitGroup.getID();
        m_unitGroupMap.emplace(unitGroupID, std::move(unitGroup));
    }
}

void ImmuneFightSimulator::run()
{
    while (true)
    {
        auto previousState{m_unitGroupMap};

        std::vector<Targeting> targetings = createTargeting();
        executeAttacks(targetings);
        removeEmptyUnitGroups();

        if (previousState == m_unitGroupMap)
        {
            break;
        }
    }
}

unsigned ImmuneFightSimulator::getTotalRemainingNumUnits() const
{
    return std::accumulate(m_unitGroupMap.cbegin(), m_unitGroupMap.cend(), 0u, [](int acc, const auto& elem)
                            {
                                return acc + elem.second.getNumUnits();
                            });
}

bool ImmuneFightSimulator::isThereRemainingFrom(Faction faction) const
{
    auto findResult = std::find_if(m_unitGroupMap.cbegin(), m_unitGroupMap.cend(), [faction](const auto& elem)
                                    {
                                        return elem.second.getFaction() == faction;
                                    });

    return findResult != m_unitGroupMap.cend();
}

std::vector<Targeting> ImmuneFightSimulator::createTargeting() const
{
    UnitGroupIDToUnitGroupIDMap targetToAttacker;

    for (const auto attackerID : getTargetingOrder())
    {
        const UnitGroup& attacker = m_unitGroupMap.at(attackerID);
        auto target = getBestTarget(attacker, targetToAttacker);

        if (target.is_initialized())
        {
            targetToAttacker.emplace(target.get().getID(), attacker.getID());
        }
    }

    std::vector<Targeting> targetings;

    for (const auto& targetToAttackerElem : targetToAttacker)
    {
        targetings.emplace_back(targetToAttackerElem.second, targetToAttackerElem.first);
    };

    return targetings;
}

void ImmuneFightSimulator::executeAttacks(std::vector<Targeting> targetings)
{
    std::sort(targetings.begin(), targetings.end(), [this](const auto& lhs, const auto& rhs)
                {
                    const auto& lhsAttacker = this->m_unitGroupMap.at(lhs.attackerID);
                    const auto& rhsAttacker = this->m_unitGroupMap.at(rhs.attackerID);

                    return lhsAttacker.getInitiative() > rhsAttacker.getInitiative();
                });

    for (const auto& targeting : targetings)
    {
        const UnitGroup& attacker = m_unitGroupMap.at(targeting.attackerID);
        UnitGroup& target = m_unitGroupMap.at(targeting.targetID);

        if (!attacker.isEmpty())
        {
            attacker.attack(target);
        }
    }
}

void ImmuneFightSimulator::removeEmptyUnitGroups()
{
    for (auto iter = m_unitGroupMap.begin(); iter != m_unitGroupMap.end();)
    {
        if (iter->second.isEmpty())
        {
            iter = m_unitGroupMap.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

std::vector<UnitGroupIDType> ImmuneFightSimulator::getTargetingOrder() const
{
    std::vector<UnitGroupIDType> targetingOrder;

    for (const auto& elem : m_unitGroupMap)
    {
        targetingOrder.push_back(elem.first);
    }

    std::sort(targetingOrder.begin(), targetingOrder.end(), [this](const auto& lhs, const auto& rhs)
                {
                    const UnitGroup& lhsUnitGroup = this->m_unitGroupMap.at(lhs);
                    const UnitGroup& rhsUnitGroup = this->m_unitGroupMap.at(rhs);

                    if (lhsUnitGroup.getEffectivePower() != rhsUnitGroup.getEffectivePower())
                    {
                        return lhsUnitGroup.getEffectivePower() > rhsUnitGroup.getEffectivePower();
                    }

                    return lhsUnitGroup.getInitiative() > rhsUnitGroup.getInitiative();
                });

    return targetingOrder;
}


boost::optional<UnitGroup> ImmuneFightSimulator::getBestTarget(const UnitGroup& attacker, const UnitGroupIDToUnitGroupIDMap& targetToAttacker) const
{
    boost::optional<UnitGroup> bestTarget;

    for (const auto& potentialTargetElem : m_unitGroupMap)
    {
        const UnitGroup& potentialTarget = potentialTargetElem.second;

        if (targetToAttacker.find(potentialTarget.getID()) != targetToAttacker.end())
        {
            continue;
        }

        bool isValidTarget = attacker.isHostileTowards(potentialTarget) && attacker.canDealDamageTo(potentialTarget);
        if (!isValidTarget)
        {
            continue;
        }

        if (isBetterTarget(attacker, bestTarget, potentialTarget))
        {
            bestTarget = potentialTarget;
        }
    }

    return bestTarget;
}

bool ImmuneFightSimulator::isBetterTarget(const UnitGroup& attacker, const boost::optional<UnitGroup>& bestTargetOpt, const UnitGroup& potentialTarget)
{
    if (!bestTargetOpt.is_initialized())
    {
        return true;
    }

    const auto& bestTarget = bestTargetOpt.get();

    if (attacker.numPossibleDamageTo(potentialTarget) != attacker.numPossibleDamageTo(bestTarget))
    {
        return attacker.numPossibleDamageTo(potentialTarget) > attacker.numPossibleDamageTo(bestTarget);
    }

    if (potentialTarget.getEffectivePower() != bestTarget.getEffectivePower())
    {
        return potentialTarget.getEffectivePower() > bestTarget.getEffectivePower();
    }

    return potentialTarget.getInitiative() > bestTarget.getInitiative();
}

}
}
}
