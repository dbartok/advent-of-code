#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_set>

#include <boost/functional/hash.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day11
{

using EnergyLevelRow = std::vector<int>;
using EnergyLevelGrid = std::vector<EnergyLevelRow>;

using Coordinates = std::pair<int, int>;
using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

class OctopusGridSimulator
{
public:
    OctopusGridSimulator(EnergyLevelGrid initialEnergyLevelGrid);

    void simulate(size_t numSteps);
    void simulateUntilSynchronizedFlash();

    unsigned getNumTotalFlashes();
    unsigned getNumStepsElapsed();

private:
    EnergyLevelGrid m_energyLevelGrid;

    const size_t m_width;
    const size_t m_height;

    unsigned m_numTotalFlashes = 0;
    unsigned m_numStepsElapsed = 0;

    void simulateDay();
    void increaseEnergyLevelAt(const Coordinates& coordinates);
    int& energyLevelAt(const Coordinates& coordinates);
    void increaseEnergyAtAdjacentCoordinates(const Coordinates& baseCoordinates);
    void resetIfFlashedAt(const Coordinates& coordinates);

    std::vector<Coordinates> getAllAdjacentCoordinates(const Coordinates& coordinates) const;
};

}
}
}
