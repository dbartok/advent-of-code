#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const int DEFAULT_HIT_POINTS = 200;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day15
{

enum class Faction
{
    ELF,
    GOBLIN,
};

class Unit;
using UnitSharedPtr = std::shared_ptr<Unit>;

using Coordinates = std::pair<unsigned, unsigned>;

class Unit
{
public:
    Unit(Faction faction, Coordinates coordinates, int attackPower)
        : m_faction{faction}
        , m_coordinates{std::move(coordinates)}
        , m_attackPower(attackPower)
        , m_hitPoints{DEFAULT_HIT_POINTS}
    {

    }

    const Coordinates& getCoordinates() const
    {
        return m_coordinates;
    }

    const Faction getFaction() const
    {
        return m_faction;
    }

    bool isHostileTowards(const Unit& other) const
    {
        return m_faction != other.getFaction();
    }

    bool isDead() const
    {
        return m_hitPoints <= 0;
    }

    int getHitPoints() const
    {
        return m_hitPoints;
    }

    void attack(Unit& other) const
    {
        other.m_hitPoints -= m_attackPower;
    }

    void setCoordinates(Coordinates coordinates)
    {
        m_coordinates = std::move(coordinates);
    }

private:
    Faction m_faction;
    Coordinates m_coordinates;
    int m_attackPower;
    int m_hitPoints;
};

}
}
}
