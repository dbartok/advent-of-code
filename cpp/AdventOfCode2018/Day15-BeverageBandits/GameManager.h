#pragma once

#include "Unit.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>

#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day15
{

using WallsGridLine = std::vector<bool>;
using WallGrid = std::vector<WallsGridLine>;

using CoordinatesToUnit = std::unordered_map<Coordinates, UnitSharedPtr, boost::hash<Coordinates>>;

struct SearchFieldInfo
{
    Coordinates initialMoveCoordinates;
    Coordinates currentCoordinates;

    SearchFieldInfo(Coordinates initialMoveCoordinates, Coordinates searchCoordinates)
        : initialMoveCoordinates{std::move(initialMoveCoordinates)}
        , currentCoordinates{std::move(searchCoordinates)}
    {

    }
};

class GameManager
{
public:
    GameManager(WallGrid wallGrid, CoordinatesToUnit coordinatesToUnit);

    void play();

    unsigned getNumTurnsElapsed() const;
    unsigned getTotalHitPointsRemaining() const;
    unsigned getNumElvesAlive() const;

private:
    WallGrid m_wallGrid;
    CoordinatesToUnit m_coordinatesToUnit;

    unsigned m_turnsElapsed = 0;

    UnitSharedPtr getAttackTarget(const Unit& unit, const Coordinates& unitCoordinates) const;
    std::vector<UnitSharedPtr> getAllNeighborUnitSharedPtrs(const Coordinates& coordinates) const;

    void maybeMoveUnit(const UnitSharedPtr& unitSharedPtr);
    void moveUnit(const UnitSharedPtr& unitSharedPtr, const Coordinates& destination);
    std::vector<SearchFieldInfo> getDestinationsWithMinimumDistance(const Unit& unit) const;

    std::vector<Coordinates> getAllFreeNeighborCoordinates(const Coordinates& coordinates) const;
    std::vector<Coordinates> getAllNeighborCoordinates(const Coordinates& coordinates) const;
    std::vector<Coordinates> filterOnlyUnoccupied(const std::vector<Coordinates>& allCoordinates) const;

    std::list<UnitSharedPtr> getUnitSharedPtrsInTurnOrder() const;

    bool isOnlyOneFactionRemaining() const;
};

}
}
}
