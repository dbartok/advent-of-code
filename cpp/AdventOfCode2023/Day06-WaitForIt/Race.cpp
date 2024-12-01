#include "Race.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day06
{

Race::Race(int64_t raceDuration, int64_t recordDistance)
    : m_raceDuration{raceDuration}
    , m_recordDistance{recordDistance}
{

}

int64_t Race::getNumWaysToBeatRecord() const
{
    const int64_t lowestButtonPressDurationThatBeatsRecord = getLowestButtonPressDurationThatBeatsRecord();
    const int64_t highestButtonPressDurationThatBeatsRecord = m_raceDuration - lowestButtonPressDurationThatBeatsRecord;
    return highestButtonPressDurationThatBeatsRecord - lowestButtonPressDurationThatBeatsRecord + 1;
}

int64_t Race::getLowestButtonPressDurationThatBeatsRecord() const
{
    int64_t lowerBound = 0;
    int64_t upperBound = m_raceDuration / 2;

    while (lowerBound != upperBound)
    {
        const int64_t midpoint = (lowerBound + upperBound) / 2;
        const int64_t distanceForMidpoint = getDistanceForButtonPressDuration(midpoint);
        if (distanceForMidpoint > m_recordDistance)
        {
            upperBound = midpoint;
        }
        else
        {
            lowerBound = midpoint + 1;
        }
    }

    return lowerBound;
}

int64_t Race::getDistanceForButtonPressDuration(int64_t buttonPressDuration) const
{
    return buttonPressDuration * (m_raceDuration - buttonPressDuration);
}

}
}
}
