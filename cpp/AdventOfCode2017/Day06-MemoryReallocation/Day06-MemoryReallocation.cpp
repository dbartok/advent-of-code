#include "Day06-MemoryReallocation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>

#include <unordered_set>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day06
{

template<typename T>
unsigned wrappingForwardDistance(const T& from, const T& to, size_t size)
{
    if (to > from)
    {
        return to - from;
    }
    else
    {
        return size - (from - to);
    }
}

void redistribute(MemoryBanks& banks)
{
    auto maxElementIter = std::max_element(banks.begin(), banks.end());
    unsigned maxValue = *maxElementIter;
    *maxElementIter = 0;

    for (auto iter = banks.begin(); iter != banks.end(); ++iter)
    {
        unsigned& bank = *iter;
        unsigned distance = wrappingForwardDistance(maxElementIter, iter, banks.size());

        unsigned increments = 0;

        if (maxValue >= distance)
        {
            // First increment
            ++increments;

            // All other subsequent increments
            unsigned remainingValue = maxValue - distance;
            increments += (remainingValue / banks.size());
        }

        bank += increments;
    }
}

unsigned numUniqueRedistributions(MemoryBanks banks)
{
    if (banks.empty())
    {
        return 1;
    }

    std::unordered_set<MemoryBanks, boost::hash<MemoryBanks>> banksOccurences;

    while (true)
    {
        bool insertionTookPlace;
        std::tie(std::ignore, insertionTookPlace) = banksOccurences.insert(banks);

        if (!insertionTookPlace)
        {
            break;
        }

        redistribute(banks);
    }

    return banksOccurences.size();
}

unsigned cyclesUntilReoccurs(MemoryBanks banks)
{
    if (banks.empty())
    {
        return 1;
    }

    std::vector<MemoryBanks> allCyclesInOrder;

    while (true)
    {
        // Could also store the unordered_set (in the same way as in part 1) in addition to the vector to improve lookup time here
        auto foundIter = std::find(allCyclesInOrder.begin(), allCyclesInOrder.end(), banks);
        if (foundIter != allCyclesInOrder.end())
        {
            return allCyclesInOrder.end() - foundIter;
        }

        allCyclesInOrder.push_back(banks);

        redistribute(banks);
    }
}

}
}
}
