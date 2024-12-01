#include "Day09-EncodingError.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day09;

TEST_CLASS(Day09EncodingError)
{
public:

    TEST_METHOD(firstInvalidNumber_SimpleTests)
    {
        Assert::AreEqual(127ll, CurrentDay::firstInvalidNumber(m_numbers, 5));
    }

    TEST_METHOD(encryptionWeakness_SimpleTests)
    {
        Assert::AreEqual(62ll, CurrentDay::encryptionWeakness(m_numbers, 5));
    }

    std::vector<int64_t> m_numbers =
    {
        35,
        20,
        15,
        25,
        47,
        40,
        62,
        55,
        65,
        95,
        102,
        117,
        150,
        182,
        127,
        219,
        299,
        277,
        309,
        576
    };

};
