#include "Day07-TheTreacheryOfWhales.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <numeric>
#include <cmath>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day07
{

int getMiddleValue(std::vector<int> vec)
{
    const size_t middleElementIndex = vec.size() / 2;
    std::nth_element(vec.begin(), vec.begin() + middleElementIndex, vec.end());
    return vec.at(middleElementIndex);
}

double getAverage(const std::vector<int>& vec)
{
    return std::accumulate(vec.cbegin(), vec.cend(), 0.0) / vec.size();
}

std::vector<int> getDistancesFromValue(std::vector<int> vec, int valueToMeasureFrom)
{
    std::transform(vec.begin(), vec.end(), vec.begin(), [valueToMeasureFrom](const auto& elem)
                   {
                       return std::abs(elem - valueToMeasureFrom);
                   });
    return vec;
}

int getAlignmentFuelCostWithNoIncrease(const std::vector<int>& horizontalPositions, int alignmentPosition)
{
    const std::vector<int> distancesFromAlignmentPosition = getDistancesFromValue(horizontalPositions, alignmentPosition);
    return std::accumulate(distancesFromAlignmentPosition.cbegin(), distancesFromAlignmentPosition.cend(), 0);
}

int getAlignmentFuelCostWithLinearIncrease(const std::vector<int>& horizontalPositions, int alignmentPosition)
{
    const std::vector<int> distancesFromAlignmentPosition = getDistancesFromValue(horizontalPositions, alignmentPosition);
    return std::accumulate(distancesFromAlignmentPosition.cbegin(), distancesFromAlignmentPosition.cend(), 0, [](const auto& acc, const auto& elem)
                           {
                               return acc + elem * (elem + 1) / 2;
                           });
}

int leastAmountOfFuelSpentToAlign(const std::vector<int>& horizontalPositions)
{
    const int middleValue = getMiddleValue(horizontalPositions);
    return getAlignmentFuelCostWithNoIncrease(horizontalPositions, middleValue);
}

int leastAmountOfFuelSpentToAlignWithIncreasingCosts(const std::vector<int>& horizontalPositions)
{
    const double average = getAverage(horizontalPositions);

    const int alignmentPositionCandidateOne = std::floor(average);
    const int alignmentPositionCandidateTwo = std::ceil(average);

    const int possibleFuelCostOne = getAlignmentFuelCostWithLinearIncrease(horizontalPositions, alignmentPositionCandidateOne);
    const int possibleFuelCostTwo = getAlignmentFuelCostWithLinearIncrease(horizontalPositions, alignmentPositionCandidateTwo);

    return std::min(possibleFuelCostOne, possibleFuelCostTwo);
}

}
}
}