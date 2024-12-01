#include "GridInfectingVirus.h"

#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cassert>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day22
{

GridInfectingVirus::GridInfectingVirus(InfiniteGrid<InfectionState> initialGrid)
    : m_grid{std::move(initialGrid)}
    , m_direction{Direction::UP}
    , m_coords{0, 0}
    , m_totalInfectionBursts{0}
{

}

void GridInfectingVirus::infectRepeatedly(unsigned numIterations)
{
    for (unsigned i = 0; i < numIterations; ++i)
    {
        makeInfectionStep();
    }
}

unsigned GridInfectingVirus::getTotalInfectionBursts() const noexcept
{
    return m_totalInfectionBursts;
}

void GridInfectingVirus::turnLeft() noexcept
{
    const int mod = static_cast<int>(Direction::_MODULUS);
    m_direction = static_cast<Direction>((static_cast<int>(m_direction) + mod - 1) % mod);
}

void GridInfectingVirus::turnRight() noexcept
{
    const int mod = static_cast<int>(Direction::_MODULUS);
    m_direction = static_cast<Direction>((static_cast<int>(m_direction) + 1) % mod);
}

void GridInfectingVirus::reverseDirection() noexcept
{
    const int mod = static_cast<int>(Direction::_MODULUS);
    m_direction = static_cast<Direction>((static_cast<int>(m_direction) + 2) % mod);
}

void GridInfectingVirus::stepForward() noexcept
{
    switch (m_direction)
    {
        case Direction::LEFT:
            m_coords.first -= 1;
            break;
        case Direction::RIGHT:
            m_coords.first += 1;
            break;
        case Direction::UP:
            m_coords.second -= 1;
            break;
        case Direction::DOWN:
            m_coords.second += 1;
            break;
        case Direction::_MODULUS:
        default:
            // Enum has invalid value
            assert(false);
    }
}

void BasicGridInfectingVirus::makeInfectionStep()
{
    const bool isCurrentCellInfected = m_grid.getValue(m_coords.first, m_coords.second) == InfectionState::INFECTED;

    if (isCurrentCellInfected)
    {
        turnRight();
        m_grid.setValue(m_coords.first, m_coords.second, InfectionState::CLEAN);
    }
    else
    {
        ++m_totalInfectionBursts;
        turnLeft();
        m_grid.setValue(m_coords.first, m_coords.second, InfectionState::INFECTED);
    }

    stepForward();
}

void EvolvedGridInfectingVirus::makeInfectionStep()
{
    const InfectionState currentCellInfectionState = m_grid.getValue(m_coords.first, m_coords.second);

    switch (currentCellInfectionState)
    {
        case InfectionState::CLEAN:
            turnLeft();
            m_grid.setValue(m_coords.first, m_coords.second, InfectionState::WEAKENED);
            break;

        case InfectionState::WEAKENED:
            m_grid.setValue(m_coords.first, m_coords.second, InfectionState::INFECTED);
            ++m_totalInfectionBursts;
            break;

        case InfectionState::INFECTED:
            turnRight();
            m_grid.setValue(m_coords.first, m_coords.second, InfectionState::FLAGGED);
            break;

        case InfectionState::FLAGGED:
            reverseDirection();
            m_grid.setValue(m_coords.first, m_coords.second, InfectionState::CLEAN);
            break;

        default:
            assert(false);
    }

    stepForward();
}

}
}
}
