#include "Day01-ChronalCalibration.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day01
{

int sumOfAllNumbers(const std::vector<int>& numbers)
{
    return std::accumulate(numbers.cbegin(), numbers.cend(), 0);
}

int firstDuplicateSumReached(const std::vector<int>& numbers)
{
    int sum = 0;
    std::unordered_set<int> occurredSums{0};
    size_t index = 0;

    while (true)
    {
        sum += numbers[index];

        const auto findResult = occurredSums.find(sum);
        if (findResult != occurredSums.end())
        {
            return sum;
        }
        else
        {
            occurredSums.insert(sum);
        }

        index += 1;
        if (index == numbers.size())
        {
            index = 0;
        }
    }
}

}
}
}
