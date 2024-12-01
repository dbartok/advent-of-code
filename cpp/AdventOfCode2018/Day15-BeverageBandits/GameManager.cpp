#include "GameManager.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>

#include <list>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day15
{

GameManager::GameManager(WallGrid wallGrid, CoordinatesToUnit coordinatesToUnit)
    : m_wallGrid{std::move(wallGrid)}
    , m_coordinatesToUnit{std::move(coordinatesToUnit)}
{

}

void GameManager::play()
{
    while (true)
    {
        std::list<UnitSharedPtr> unitSharedPtrsInTurnOrder = getUnitSharedPtrsInTurnOrder();

        for (auto unitIter = unitSharedPtrsInTurnOrder.begin(); unitIter != unitSharedPtrsInTurnOrder.end(); ++unitIter)
        {
            if (isOnlyOneFactionRemaining())
            {
                return;
            }

            UnitSharedPtr unitSharedPtr = *unitIter;

            maybeMoveUnit(unitSharedPtr);

            auto attackTargetSharedPtr = getAttackTarget(*unitSharedPtr, unitSharedPtr->getCoordinates());
            if (attackTargetSharedPtr)
            {
                unitSharedPtr->attack(*attackTargetSharedPtr);
                if (attackTargetSharedPtr->isDead())
                {
                    auto removalBeginIter = std::remove(unitSharedPtrsInTurnOrder.begin(), unitSharedPtrsInTurnOrder.end(), attackTargetSharedPtr);
                    unitSharedPtrsInTurnOrder.erase(removalBeginIter, unitSharedPtrsInTurnOrder.end());
                    m_coordinatesToUnit.erase(attackTargetSharedPtr->getCoordinates());

                    // Iterator might have been invalidated, so we look it up again
                    unitIter = std::find(unitSharedPtrsInTurnOrder.begin(), unitSharedPtrsInTurnOrder.end(), unitSharedPtr);
                }
            }
        }

        ++m_turnsElapsed;
    }
}

unsigned GameManager::getNumTurnsElapsed() const
{
    return m_turnsElapsed;
}

unsigned GameManager::getTotalHitPointsRemaining() const
{
    return std::accumulate(m_coordinatesToUnit.cbegin(), m_coordinatesToUnit.cend(), 0, [](int acc, const auto& elem)
                            {
                                return acc + elem.second->getHitPoints();
                            });
}

unsigned GameManager::getNumElvesAlive() const
{
    return std::count_if(m_coordinatesToUnit.cbegin(), m_coordinatesToUnit.cend(), [](const auto& elem)
                            {
                                return elem.second->getFaction() == Faction::ELF;
                            });
}

UnitSharedPtr GameManager::getAttackTarget(const Unit& unit, const Coordinates& unitCoordinates) const
{
    UnitSharedPtr target = nullptr;

    std::vector<UnitSharedPtr> neighborUnitSharedPtrs = getAllNeighborUnitSharedPtrs(unitCoordinates);
    for (const auto& neighborUnitSharedPtr : neighborUnitSharedPtrs)
    {
        if (unit.isHostileTowards(*neighborUnitSharedPtr))
        {
            if (!target || neighborUnitSharedPtr->getHitPoints() < target->getHitPoints())
            {
                target = neighborUnitSharedPtr;
            }
        }
    }

    return target;
}


std::vector<UnitSharedPtr> GameManager::getAllNeighborUnitSharedPtrs(const Coordinates& coordinates) const
{
    auto allNeighborCoordinates = getAllNeighborCoordinates(coordinates);

    std::vector<UnitSharedPtr> allNeighborUnitSharedPtrs;

    for (const auto& neighborCoordinates : allNeighborCoordinates)
    {
        const auto findResult = m_coordinatesToUnit.find(neighborCoordinates);
        if (findResult != m_coordinatesToUnit.end())
        {
            allNeighborUnitSharedPtrs.push_back(findResult->second);
        }
    }

    return allNeighborUnitSharedPtrs;
}

void GameManager::maybeMoveUnit(const UnitSharedPtr& unitSharedPtr)
{
    if (getAttackTarget(*unitSharedPtr, unitSharedPtr->getCoordinates()))
    {
        return;
    }

    std::vector<SearchFieldInfo> possibleDestinations = getDestinationsWithMinimumDistance(*unitSharedPtr);

    if (!possibleDestinations.empty())
    {
        auto selectedDestinationIter = std::min_element(possibleDestinations.begin(), possibleDestinations.end(),
                                                        [](const auto& lhs, const auto& rhs)
                                                        {
                                                            return lhs.currentCoordinates < rhs.currentCoordinates;
                                                        });

        moveUnit(unitSharedPtr, selectedDestinationIter->initialMoveCoordinates);
    }
}

void GameManager::moveUnit(const UnitSharedPtr& unitSharedPtr, const Coordinates& destination)
{
    m_coordinatesToUnit.erase(unitSharedPtr->getCoordinates());
    unitSharedPtr->setCoordinates(destination);
    m_coordinatesToUnit.emplace(unitSharedPtr->getCoordinates(), unitSharedPtr);
}

std::vector<SearchFieldInfo> GameManager::getDestinationsWithMinimumDistance(const Unit& unit) const
{
    std::queue<SearchFieldInfo> currentDistanceQueue;
    std::unordered_set<Coordinates, boost::hash<Coordinates>> visitedCoordinates;

    for (const auto& initialFreeNeighborCoordinates : getAllFreeNeighborCoordinates(unit.getCoordinates()))
    {
        currentDistanceQueue.push({initialFreeNeighborCoordinates, initialFreeNeighborCoordinates});
        visitedCoordinates.insert(initialFreeNeighborCoordinates);
    }

    std::vector<SearchFieldInfo> possibleDestinations;
    std::queue<SearchFieldInfo> nextDistanceQueue;

    while (possibleDestinations.empty() && !currentDistanceQueue.empty())
    {
        while (!currentDistanceQueue.empty())
        {
            auto currentSearchItem = currentDistanceQueue.front();
            currentDistanceQueue.pop();

            if (getAttackTarget(unit, currentSearchItem.currentCoordinates))
            {
                possibleDestinations.push_back(currentSearchItem);
            }

            for (const auto& freeNeighborCoordinates : getAllFreeNeighborCoordinates(currentSearchItem.currentCoordinates))
            {
                if (visitedCoordinates.insert(freeNeighborCoordinates).second)
                {
                    nextDistanceQueue.push({currentSearchItem.initialMoveCoordinates, freeNeighborCoordinates});
                }
            }
        }

        std::swap(currentDistanceQueue, nextDistanceQueue);
    }

    return possibleDestinations;
}

std::vector<Coordinates> GameManager::getAllFreeNeighborCoordinates(const Coordinates& coordinates) const
{
    auto allNeighborCoordinates = getAllNeighborCoordinates(coordinates);
    return filterOnlyUnoccupied(allNeighborCoordinates);
}

std::vector<Coordinates> GameManager::getAllNeighborCoordinates(const Coordinates& coordinates) const
{
    std::vector<Coordinates> neighborCoordinates;

    if (coordinates.second > 0)
    {
        neighborCoordinates.emplace_back(coordinates.first - 1, coordinates.second);
    }

    if (coordinates.first > 0)
    {
        neighborCoordinates.emplace_back(coordinates.first, coordinates.second - 1);
    }

    if (coordinates.first < m_wallGrid[coordinates.second].size() - 1)
    {
        neighborCoordinates.emplace_back(coordinates.first, coordinates.second + 1);
    }

    if (coordinates.second < m_wallGrid.size() - 1)
    {
        neighborCoordinates.emplace_back(coordinates.first + 1, coordinates.second);
    }

    return neighborCoordinates;
}

std::vector<Coordinates> GameManager::filterOnlyUnoccupied(const std::vector<Coordinates>& allCoordinates) const
{
    std::vector<Coordinates> unoccupiedCoordinates;

    std::copy_if(allCoordinates.cbegin(), allCoordinates.cend(), std::back_inserter(unoccupiedCoordinates),
                    [this](const Coordinates& coordinates)
                    {
                        const bool notWall = !this->m_wallGrid[coordinates.first][coordinates.second];
                        const bool notUnit = this->m_coordinatesToUnit.find(coordinates) == this->m_coordinatesToUnit.end();

                        return notWall && notUnit;
                    });

    return unoccupiedCoordinates;
}

std::list<UnitSharedPtr> GameManager::getUnitSharedPtrsInTurnOrder() const
{
    std::vector<UnitSharedPtr> unitSharedPtrs;

    std::transform(m_coordinatesToUnit.cbegin(), m_coordinatesToUnit.cend(), std::back_inserter(unitSharedPtrs),
                    [](const auto& elem)
                    {
                        return elem.second;
                    });

    std::sort(unitSharedPtrs.begin(), unitSharedPtrs.end(),
                [](const UnitSharedPtr& lhs, const UnitSharedPtr& rhs)
                {
                    return lhs->getCoordinates() < rhs->getCoordinates();
                });

    return {std::make_move_iterator(unitSharedPtrs.begin()), std::make_move_iterator(unitSharedPtrs.end())};
}

bool GameManager::isOnlyOneFactionRemaining() const
{
    return Utils::allElementsEqual(m_coordinatesToUnit.cbegin(), m_coordinatesToUnit.cend(), [](const auto& lhs, const auto& rhs)
                                    {
                                        return lhs.second->getFaction() == rhs.second->getFaction();
                                    });
}

}
}
}
