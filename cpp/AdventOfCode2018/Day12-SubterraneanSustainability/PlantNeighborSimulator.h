#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_set>
#include <array>
#include <deque>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day12
{

using Pots = std::unordered_set<int>;
using NeighborPattern = std::array<bool, 5>;

class PlantNeighborSimulator
{
public:
    PlantNeighborSimulator(Pots initialPotsWithPlants, std::vector<NeighborPattern> neighborPatternsResultingInPlant);

    void simulateGrowth(unsigned long long numCycles);

    long long getSumOfPotNumbersWithPlant() const noexcept;

private:
    static const unsigned NUM_MAX_LAST_GROWTH_DIFFS = 100;

    Pots m_potsWithPlants;

    std::vector<NeighborPattern> m_neighborPatternsResultingInPlant;

    long long m_currentSumOfPotNumbersWithPlant;
    std::deque<long long> m_latestGrowthValues;

    void executeGrowthCycle();
    void executeGrowthCycleInPotRange(int begin, int end);
    bool isPlantInNextCycle(int potNumber) const;
    NeighborPattern getNeighborPattern(int potNumber) const;

    void recalculateGrowthValues();
    bool isGrowthInStableState() const;
};

}
}
}
