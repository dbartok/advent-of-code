#include "Day02-CorruptedChecksum.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day02
{

unsigned checkSumDiffSmallestLargest(const RowsOfNumbers& rows)
{
    unsigned checkSum = 0;

    for (const auto& row : rows)
    {
        if (row.empty())
        {
            continue;
        }

        unsigned maxElement = *std::max_element(row.begin(), row.end());
        unsigned minElement = *std::min_element(row.begin(), row.end());
        checkSum += (maxElement - minElement);
    }

    return checkSum;
}

unsigned sumEvenlyDivisbleValues(const RowsOfNumbers& rows)
{
    unsigned sum = 0;

    for (const auto& row : rows)
    {
        for (size_t i = 0; i < row.size(); i++)
        {
            for (size_t j = i + 1; j < row.size(); j++)
            {
                unsigned dividend = std::max(row[i], row[j]);
                unsigned divisor = std::min(row[i], row[j]);

                if (dividend % divisor == 0)
                {
                    sum += dividend / divisor;
                    break;
                }
            }
        }
    }

    return sum;
}

}
}
}
