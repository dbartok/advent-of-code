#include "Day25-FullOfHotAir.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char SNAFU_MINUS_ONE = '-';
const char SNAFU_MINUS_TWO = '=';
const int SNAFU_NUMBER_SYSTEM_BASE = 5;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day25
{

int snafuCharToDigit(char snafuChar)
{
    switch (snafuChar)
    {
        case SNAFU_MINUS_ONE:
            return -1;
        case SNAFU_MINUS_TWO:
            return -2;
        default:
            return snafuChar - '0';
    }
}

char digitToSnafuChar(int value)
{
    switch (value)
    {
        case -1:
            return SNAFU_MINUS_ONE;
        case -2:
            return SNAFU_MINUS_TWO;
        default:
            return static_cast<char>(value) + '0';
    }
}

int getSnafuModulus(int64_t value)
{
    if ((value + 1) % SNAFU_NUMBER_SYSTEM_BASE == 0)
    {
        return -1;
    }

    if ((value + 2) % SNAFU_NUMBER_SYSTEM_BASE == 0)
    {
        return -2;
    }

    return value % SNAFU_NUMBER_SYSTEM_BASE;
}

int64_t snafuToDecimal(const std::string& snafuNumberString)
{
    int64_t decimalResult = 0;
    int64_t valueMultiplier = 1;

    for (auto snafuCharIter = snafuNumberString.crbegin(); snafuCharIter != snafuNumberString.crend(); ++snafuCharIter)
    {
        const char snafuChar = *snafuCharIter;
        const int digit = snafuCharToDigit(snafuChar);

        decimalResult += digit * valueMultiplier;

        valueMultiplier *= SNAFU_NUMBER_SYSTEM_BASE;
    }

    return decimalResult;
}

std::string decimalToSnafu(int64_t decimal)
{
    std::string snafuResult;

    while (decimal > 0)
    {
        const int digit = getSnafuModulus(decimal);
        const char snafuChar = digitToSnafuChar(digit);
        snafuResult = snafuChar + snafuResult;

        decimal -= digit;
        decimal /= SNAFU_NUMBER_SYSTEM_BASE;
    }

    return snafuResult;
}

std::string snafuNumberRequiredForConsole(const std::vector<std::string>& snafuNumberLines)
{
    const int64_t sum = std::accumulate(snafuNumberLines.cbegin(), snafuNumberLines.cend(), 0ll, [](const auto acc, const auto& snafuNumberString) {return acc + snafuToDecimal(snafuNumberString); });
    return decimalToSnafu(sum);
}

}
}
}