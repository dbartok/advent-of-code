#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cstdint>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day06
{

class Race
{
public:
    Race(int64_t raceDuration, int64_t recordDistance);

    int64_t getNumWaysToBeatRecord() const;

private:
    int64_t m_raceDuration;
    int64_t m_recordDistance;

    int64_t getLowestButtonPressDurationThatBeatsRecord() const;
    int64_t getDistanceForButtonPressDuration(int64_t buttonPressDuration) const;
};

}
}
}
