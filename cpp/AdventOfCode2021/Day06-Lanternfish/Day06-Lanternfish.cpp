#include "Day06-Lanternfish.h"

#include "LanterfishSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned NUM_DAYS_FIRST_PART = 80;
const unsigned NUM_DAYS_SECOND_PART = 256;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day06
{

uint64_t numLanternfishAfterSmallNumberOfDays(const std::vector<int>& initialState)
{
    LanterfishSimulator lanternfishSimulator{initialState};
    lanternfishSimulator.simulateDays(NUM_DAYS_FIRST_PART);
    return lanternfishSimulator.getNumTotalFish();
}

uint64_t numLanternfishAfterLargeNumberOfDays(const std::vector<int>& initialState)
{
    LanterfishSimulator lanternfishSimulator{initialState};
    lanternfishSimulator.simulateDays(NUM_DAYS_SECOND_PART);
    return lanternfishSimulator.getNumTotalFish();
}

}
}
}