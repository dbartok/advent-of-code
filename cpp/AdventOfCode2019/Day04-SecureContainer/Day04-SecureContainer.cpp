#include "Day04-SecureContainer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day04
{

std::vector<int> convertIntToDigitVector(int number)
{
    std::vector<int> digits;

    while (number > 0)
    {
        digits.push_back(number % 10);
        number /= 10;
    }

    std::reverse(digits.begin(), digits.end());

    return digits;
}

bool areDigitsIncreasing(const std::vector<int>& digits)
{
    boost::optional<int> previousDigit{};

    for (const auto digit : digits)
    {
        if (digit < previousDigit)
        {
            return false;
        }

        previousDigit = digit;
    }

    return true;
}

bool hasTwoAdjacentEqualDigits(const std::vector<int>& digits)
{
    boost::optional<int> previousDigit{};

    for (const auto digit : digits)
    {
        if (digit == previousDigit)
        {
            return true;
        }

        previousDigit = digit;
    }

    return false;
}

bool hasTwoAdjacentEqualDigitsNotPartOfLargerGroup(const std::vector<int>& digits)
{
    for (size_t i = 0; i < digits.size() - 1; ++i)
    {
        size_t equalGroupEndIndex = i;
        for (; equalGroupEndIndex < digits.size() - 1 && digits.at(equalGroupEndIndex) == digits.at(equalGroupEndIndex + 1); ++equalGroupEndIndex)
        {
        }

        if (equalGroupEndIndex == i + 1)
        {
            return true;
        }

        i = equalGroupEndIndex;
    }

    return false;
}


unsigned numDifferentValidPasswords(int lowerBound, int upperBound, std::function<bool(std::vector<int>)> validatorFunc)
{
    unsigned numValidPasswords = 0;

    for (int candidate = lowerBound; candidate <= upperBound; ++candidate)
    {
        std::vector<int> digits = convertIntToDigitVector(candidate);

        if (validatorFunc(digits))
        {
            ++numValidPasswords;
        }
    }

    return numValidPasswords;
}

unsigned numDifferentValidPasswordsSimple(int lowerBound, int upperBound)
{
    return numDifferentValidPasswords(lowerBound, upperBound,
                                      [](const auto& digits)
                                      {
                                          return areDigitsIncreasing(digits) && hasTwoAdjacentEqualDigits(digits);
                                      });
}

unsigned numDifferentValidPasswordsLargerGroupIsNotMatching(int lowerBound, int upperBound)
{
    return numDifferentValidPasswords(lowerBound, upperBound,
                                      [](const auto& digits)
                                      {
                                          return areDigitsIncreasing(digits) && hasTwoAdjacentEqualDigitsNotPartOfLargerGroup(digits);
                                      });
}

}
}
}
