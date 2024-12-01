#include "Day15-RambunctiousRecitation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const size_t SMALL_N = 2020;
const size_t LARGE_N = 30'000'000;

}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day15
{

int nthNumberSpoken(const std::vector<int>& startingNumbers, size_t N)
{
    std::unordered_map<int, size_t> numberToLastSpokenIndex;

    for (size_t i = 0; i < startingNumbers.size() - 1; ++i)
    {
        numberToLastSpokenIndex.emplace(startingNumbers.at(i), i);
    }

    int mostRecentlySpokenNumber = startingNumbers.back();
    int numberInThisTurn = -1;
    for (size_t turnIndex = startingNumbers.size(); turnIndex < N; ++turnIndex)
    {
        const auto mostRecentlySpokenNumberLastSpokenIter = numberToLastSpokenIndex.find(mostRecentlySpokenNumber);
        if (mostRecentlySpokenNumberLastSpokenIter != numberToLastSpokenIndex.cend())
        {
            numberInThisTurn = (turnIndex - 1) - mostRecentlySpokenNumberLastSpokenIter->second;
        }
        else
        {
            numberInThisTurn = 0;
        }

        numberToLastSpokenIndex[mostRecentlySpokenNumber] = turnIndex - 1;
        mostRecentlySpokenNumber = numberInThisTurn;
    }

    return mostRecentlySpokenNumber;
}

int nthNumberSpokenSmallN(const std::vector<int>& startingNumbers)
{
    return nthNumberSpoken(startingNumbers, SMALL_N);
}

int nthNumberSpokenLargeN(const std::vector<int>& startingNumbers)
{
    return nthNumberSpoken(startingNumbers, LARGE_N);
}

}
}
}
