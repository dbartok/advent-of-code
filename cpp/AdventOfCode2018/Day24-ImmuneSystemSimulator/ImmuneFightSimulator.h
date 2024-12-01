#pragma once

#include "UnitGroup.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day24
{

using UnitGroupIDToUnitGroupIDMap = std::unordered_map<UnitGroupIDType, UnitGroupIDType>;
using UnitGroupIDToUnitGroupMap = std::unordered_map<UnitGroupIDType, UnitGroup>;

struct Targeting
{
    UnitGroupIDType attackerID;
    UnitGroupIDType targetID;

    Targeting(UnitGroupIDType attackerID, UnitGroupIDType targetID)
        : attackerID{attackerID}
        , targetID{targetID}
    {

    }
};

class ImmuneFightSimulator
{
public:
    ImmuneFightSimulator(std::vector<UnitGroup> unitGroups);

    void run();

    unsigned getTotalRemainingNumUnits() const;
    bool isThereRemainingFrom(Faction faction) const;

private:
    UnitGroupIDToUnitGroupMap m_unitGroupMap;

    std::vector<Targeting> createTargeting() const;
    void executeAttacks(std::vector<Targeting> targetings);
    void removeEmptyUnitGroups();

    std::vector<UnitGroupIDType> getTargetingOrder() const;
    boost::optional<UnitGroup> getBestTarget(const UnitGroup& attacker, const UnitGroupIDToUnitGroupIDMap& targetToAttacker) const;

    static bool isBetterTarget(const UnitGroup& attacker, const boost::optional<UnitGroup>& bestTargetOpt, const UnitGroup& potentialTarget);
};

}
}
}
