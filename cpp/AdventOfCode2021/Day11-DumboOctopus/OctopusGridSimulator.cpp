#include "OctopusGridSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int FLASH_ENERGY_LEVEL_THRESOLD = 10;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day11
{

OctopusGridSimulator::OctopusGridSimulator(EnergyLevelGrid initialEnergyLevelGrid)
    : m_energyLevelGrid{std::move(initialEnergyLevelGrid)}
    , m_width{m_energyLevelGrid.at(0).size()}
    , m_height{m_energyLevelGrid.size()}
{

}

void OctopusGridSimulator::simulate(size_t numSteps)
{
    for (size_t step = 0; step < numSteps; ++step)
    {
        simulateDay();
    }
}

void OctopusGridSimulator::simulateUntilSynchronizedFlash()
{
    unsigned allPreviousStepsNumFlashes = 0;

    while (true)
    {
        simulateDay();

        const unsigned currentStepNumFlashes = m_numTotalFlashes - allPreviousStepsNumFlashes;
        if (currentStepNumFlashes == m_height * m_width)
        {
            break;
        }

        allPreviousStepsNumFlashes += currentStepNumFlashes;
    }
}

unsigned OctopusGridSimulator::getNumTotalFlashes()
{
    return m_numTotalFlashes;
}

unsigned OctopusGridSimulator::getNumStepsElapsed()
{
    return m_numStepsElapsed;
}

void OctopusGridSimulator::simulateDay()
{
    ++m_numStepsElapsed;

    for (size_t j = 0; j < m_height; ++j)
    {
        for (size_t i = 0; i < m_width; ++i)
        {
            increaseEnergyLevelAt({i, j});
        }
    }

    for (size_t j = 0; j < m_height; ++j)
    {
        for (size_t i = 0; i < m_width; ++i)
        {
            resetIfFlashedAt({i, j});
        }
    }
}

void OctopusGridSimulator::increaseEnergyLevelAt(const Coordinates& coordinates)
{
    const int newEnergyLevel = ++energyLevelAt(coordinates);

    if (newEnergyLevel == FLASH_ENERGY_LEVEL_THRESOLD)
    {
        increaseEnergyAtAdjacentCoordinates(coordinates);
        ++m_numTotalFlashes;
    }
}

int& OctopusGridSimulator::energyLevelAt(const Coordinates& coordinates)
{
    return m_energyLevelGrid.at(coordinates.second).at(coordinates.first);
}

void OctopusGridSimulator::increaseEnergyAtAdjacentCoordinates(const Coordinates& baseCoordinates)
{
    const std::vector<Coordinates> allAdjacentCoordinates = getAllAdjacentCoordinates(baseCoordinates);

    for (const auto& coordinates : allAdjacentCoordinates)
    {
        increaseEnergyLevelAt(coordinates);
    }
}

void OctopusGridSimulator::resetIfFlashedAt(const Coordinates& coordinates)
{
    int& energyLevel = energyLevelAt(coordinates);
    if (energyLevel >= FLASH_ENERGY_LEVEL_THRESOLD)
    {
        energyLevel = 0;
    }
}

std::vector<Coordinates> OctopusGridSimulator::getAllAdjacentCoordinates(const Coordinates& coordinates) const
{
    const size_t yMin = std::max(0, coordinates.second - 1);
    const size_t yMax = std::min(static_cast<int>(m_height) - 1, coordinates.second + 1);

    const size_t xMin = std::max(0, coordinates.first - 1);
    const size_t xMax = std::min(static_cast<int>(m_width) - 1, coordinates.first + 1);

    std::vector<Coordinates> allAdjacentCoordinates;

    for (size_t j = yMin; j <= yMax; ++j)
    {
        for (size_t i = xMin; i <= xMax; ++i)
        {
            if (!(i == coordinates.first && j == coordinates.second))
            {
                allAdjacentCoordinates.emplace_back(i, j);
            }
        }
    }

    return allAdjacentCoordinates;
}

}
}
}
