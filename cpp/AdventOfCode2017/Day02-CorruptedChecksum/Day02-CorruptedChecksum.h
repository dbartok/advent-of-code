#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day02
{

using RowOfNumbers = std::vector<unsigned>;
using RowsOfNumbers = std::vector<RowOfNumbers>;

unsigned checkSumDiffSmallestLargest(const RowsOfNumbers& rows);
unsigned sumEvenlyDivisbleValues(const RowsOfNumbers& rows);

}
}
}
