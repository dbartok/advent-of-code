#include "LanterfishSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const size_t NEW_FISH_SPAWN_TIMER = 8;
const size_t EXISTING_FISH_RESET_TIMER = 6;
static_assert(NEW_FISH_SPAWN_TIMER >= EXISTING_FISH_RESET_TIMER, "New fish spawn timer must be larger than the reset timer for existing fish");

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day06
{

LanterfishSimulator::LanterfishSimulator(const std::vector<int>& initialState)
    : m_timerToNumFish(NEW_FISH_SPAWN_TIMER + 1)
{
    for (const auto timer : initialState)
    {
        ++m_timerToNumFish.at(timer);
    }
}

void LanterfishSimulator::simulateDays(unsigned numRounds)
{
    for (size_t i = 0; i < numRounds; ++i)
    {
        simulateDay();
    }
}

uint64_t LanterfishSimulator::getNumTotalFish() const
{
    return std::accumulate(m_timerToNumFish.cbegin(), m_timerToNumFish.cend(), 0ull, [](const auto& acc, const auto& elem)
                            {
                                return acc + elem;
                            });
}

void LanterfishSimulator::simulateDay()
{
    const uint64_t numFishWithZeroTimer = m_timerToNumFish.at(0);
    m_timerToNumFish.erase(m_timerToNumFish.begin());
    m_timerToNumFish.push_back(numFishWithZeroTimer);
    m_timerToNumFish.at(EXISTING_FISH_RESET_TIMER) += numFishWithZeroTimer;
}

}
}
}
