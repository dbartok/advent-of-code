#include "Day10-AdapterArray.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day10;

TEST_CLASS(Day10AdapterArray)
{
public:

    TEST_METHOD(numOneAndThreeJoltDifferencesMultiplied_SimpleTests)
    {
        Assert::AreEqual(7 * 5, CurrentDay::numOneAndThreeJoltDifferencesMultiplied(m_joltageRatingsShort));
        Assert::AreEqual(22 * 10, CurrentDay::numOneAndThreeJoltDifferencesMultiplied(m_joltageRatingsLong));

    }

    TEST_METHOD(numDistinctAdapterArrangements_SimpleTests)
    {
        Assert::AreEqual(8ll, CurrentDay::numDistinctAdapterArrangements(m_joltageRatingsShort));
        Assert::AreEqual(19208ll, CurrentDay::numDistinctAdapterArrangements(m_joltageRatingsLong));
    }

private:
    std::vector<int> m_joltageRatingsShort =
    {
        16,
        10,
        15,
        5,
        1,
        11,
        7,
        19,
        6,
        12,
        4
    };

    std::vector<int> m_joltageRatingsLong =
    {
        28,
        33,
        18,
        42,
        31,
        14,
        46,
        20,
        48,
        47,
        24,
        23,
        49,
        45,
        19,
        38,
        39,
        11,
        1,
        32,
        25,
        35,
        8,
        17,
        7,
        9,
        4,
        2,
        34,
        10,
        3
    };

};
