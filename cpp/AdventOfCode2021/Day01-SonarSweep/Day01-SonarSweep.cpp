#include "Day01-SonarSweep.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day01
{

unsigned numDepthMeasurementIncreases(const std::vector<unsigned>& depthMeasurements)
{
    return numDepthMeasurementIncreasesWithRollingWindow(depthMeasurements, 1u /*rolling_window_size*/);
}

unsigned numDepthMeasurementIncreasesWithRollingWindow(const std::vector<unsigned>& depthMeasurements, int rolling_window_size)
{
    unsigned previousWindowSum = 0;
    unsigned currentWindowSum = 0;

    for (auto initializationIter = depthMeasurements.cbegin(); initializationIter < depthMeasurements.cbegin() + rolling_window_size; ++initializationIter)
    {
        previousWindowSum += *initializationIter;
        currentWindowSum += *(std::next(initializationIter));
    }

    unsigned numIncreases = 0;

    for (auto depthMeasurementIter = depthMeasurements.cbegin() + rolling_window_size + 1; ; ++depthMeasurementIter)
    {
        if (currentWindowSum > previousWindowSum)
        {
            ++numIncreases;
        }

        if (depthMeasurementIter == depthMeasurements.cend())
        {
            break;
        }

        currentWindowSum -= *(depthMeasurementIter - rolling_window_size);
        previousWindowSum -= *(depthMeasurementIter - rolling_window_size - 1);

        currentWindowSum += *(depthMeasurementIter);
        previousWindowSum += *(depthMeasurementIter - 1);
    }

    return numIncreases;
}

}
}
}