#include "Day09-EncodingError.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <deque>
#include <unordered_set>
#include <stdexcept>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day09
{

template<typename ContainerType>
bool isNumberTheSumOfTwoNumbers(int64_t target, const ContainerType& numbers)
{
    const std::unordered_set<int64_t> seenSoFar{numbers.cbegin(), numbers.cend()};

    return std::any_of(seenSoFar.cbegin(), seenSoFar.cend(), [&seenSoFar, target](const auto& elem)
                       {
                           return (elem != target / 2) && seenSoFar.find(target - elem) != seenSoFar.cend();
                       });
}


int64_t firstInvalidNumber(const std::vector<int64_t>& numbers, size_t windowLength)
{
    std::deque<int64_t> previousNumbersInWindow{numbers.cbegin(), numbers.cbegin() + windowLength};

    for (auto numberIter = numbers.cbegin() + windowLength; numberIter != numbers.cend(); ++numberIter)
    {
        bool isValidNumber = isNumberTheSumOfTwoNumbers(*numberIter, previousNumbersInWindow);
        if (!isValidNumber)
        {
            return *numberIter;
        }

        previousNumbersInWindow.pop_front();
        previousNumbersInWindow.push_back(*numberIter);
    }

    throw std::runtime_error("No invalid numbers found.");
}

int64_t encryptionWeakness(const std::vector<int64_t>& numbers, size_t windowLength)
{
    int64_t target = firstInvalidNumber(numbers, windowLength);

    std::deque<int64_t> window;
    int64_t currentSum = 0;

    for (auto number : numbers)
    {
        window.push_back(number);
        currentSum += number;

        while (currentSum > target)
        {
            currentSum -= window.front();
            window.pop_front();
        }

        if (currentSum == target)
        {
            auto minmaxIter = std::minmax_element(window.cbegin(), window.cend());
            return *minmaxIter.first + *minmaxIter.second;
        }
    }

    throw std::runtime_error("Cannot find encryption weakness.");
}

}
}
}
