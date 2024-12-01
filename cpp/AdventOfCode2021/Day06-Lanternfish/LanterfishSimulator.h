#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day06
{

class LanterfishSimulator
{
public:
    LanterfishSimulator(const std::vector<int>& initialState);

    void simulateDays(unsigned numRounds);

    uint64_t getNumTotalFish() const;

private:
    std::vector<uint64_t> m_timerToNumFish;

    void simulateDay();
};

}
}
}
