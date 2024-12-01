#include "PlantNeighborSimulator.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day12
{

PlantNeighborSimulator::PlantNeighborSimulator(Pots initialPotsWithPlants, std::vector<NeighborPattern> neighborPatternsResultingInPlant)
        : m_potsWithPlants{std::move(initialPotsWithPlants)}
        , m_neighborPatternsResultingInPlant{std::move(neighborPatternsResultingInPlant)}
        , m_currentSumOfPotNumbersWithPlant{}
        , m_latestGrowthValues{}
{
    recalculateGrowthValues();
}

void PlantNeighborSimulator::simulateGrowth(unsigned long long numCycles)
{
    for (unsigned i = 1; i <= numCycles; ++i)
    {
        executeGrowthCycle();

        // Possible short circuit to last value
        if (isGrowthInStableState())
        {
            const long long growthValue = m_latestGrowthValues.back();
            const unsigned long long numRemainingCycles = numCycles - i;
            m_currentSumOfPotNumbersWithPlant += numRemainingCycles * growthValue;
            break;
        }
    }
}

long long PlantNeighborSimulator::getSumOfPotNumbersWithPlant() const noexcept
{
    return m_currentSumOfPotNumbersWithPlant;
}

void PlantNeighborSimulator::executeGrowthCycle()
{
    auto minMaxPotsWithPlants = std::minmax_element(m_potsWithPlants.cbegin(), m_potsWithPlants.cend());

    const int possibleChangesRangeBegin = *minMaxPotsWithPlants.first - 2;
    const int possibleChangesRangeEnd = *minMaxPotsWithPlants.second + 3;

    executeGrowthCycleInPotRange(possibleChangesRangeBegin, possibleChangesRangeEnd);

    recalculateGrowthValues();
}

void PlantNeighborSimulator::executeGrowthCycleInPotRange(int begin, int end)
{
    Pots newPotsWithPlants;

    for (int i = begin; i < end; ++i)
    {
        if (isPlantInNextCycle(i))
        {
            newPotsWithPlants.insert(i);
        }
    }

    m_potsWithPlants = newPotsWithPlants;
}

bool PlantNeighborSimulator::isPlantInNextCycle(int potNumber) const
{
    const NeighborPattern neighborPattern = getNeighborPattern(potNumber);

    const auto findResult = std::find(m_neighborPatternsResultingInPlant.cbegin(), m_neighborPatternsResultingInPlant.cend(), neighborPattern);

    return findResult != m_neighborPatternsResultingInPlant.cend();
}

NeighborPattern PlantNeighborSimulator::getNeighborPattern(int potNumber) const
{
    NeighborPattern neighborPattern{};

    size_t neighborPatternIndex = 0;
    for (int i = potNumber - 2; i < potNumber + 3; ++i)
    {
        bool isPlant = (m_potsWithPlants.find(i) != m_potsWithPlants.end());

        neighborPattern[neighborPatternIndex++] = isPlant;
    }

    return neighborPattern;
}

void PlantNeighborSimulator::recalculateGrowthValues()
{
    const long long previousSumOfPotNumbersWithPlant = m_currentSumOfPotNumbersWithPlant;
    m_currentSumOfPotNumbersWithPlant = std::accumulate(m_potsWithPlants.cbegin(), m_potsWithPlants.cend(), 0ll);

    if (m_latestGrowthValues.size() == NUM_MAX_LAST_GROWTH_DIFFS)
    {
        m_latestGrowthValues.erase(m_latestGrowthValues.begin());
    }

    m_latestGrowthValues.push_back(m_currentSumOfPotNumbersWithPlant - previousSumOfPotNumbersWithPlant);
}

bool PlantNeighborSimulator::isGrowthInStableState() const
{
    return (m_latestGrowthValues.size() == NUM_MAX_LAST_GROWTH_DIFFS) && Utils::allElementsEqual(m_latestGrowthValues.cbegin(), m_latestGrowthValues.cend());
}

}
}
}
