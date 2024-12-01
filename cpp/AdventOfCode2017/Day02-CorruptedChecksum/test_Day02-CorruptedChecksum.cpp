#include "Day02-CorruptedChecksum.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day02;

TEST_CLASS(Day02CorruptedChecksum)
{
public:

    TEST_METHOD(checkSumDiffSmallestLargest_SimpleTests)
    {
        CurrentDay::RowsOfNumbers rows =
        {
            {5, 1, 9, 5},
            {7, 5, 3,  },
            {2, 4, 6, 8}
        };

        Assert::AreEqual(18u, CurrentDay::checkSumDiffSmallestLargest(rows));
    }

    TEST_METHOD(sumEvenlyDivisbleValues_SimpleTests)
    {
        CurrentDay::RowsOfNumbers rows =
        {
            {5, 9, 2, 8},
            {9, 4, 7, 3},
            {3, 8, 6, 5}
        };

        Assert::AreEqual(9u, CurrentDay::sumEvenlyDivisbleValues(rows));
    }

};
