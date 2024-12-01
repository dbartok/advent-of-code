#include "Day05-BinaryBoarding.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day05;

TEST_CLASS(Day05BinaryBoarding)
{
public:

    TEST_METHOD(highestSeatID_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "FBFBBFFRLR",
            "BFFFBBFRRR",
            "FFFBBBFRRR",
            "BBFFBBFRLL",
        };

        Assert::AreEqual(820, CurrentDay::highestSeatID(lines));
    }

    TEST_METHOD(missingSeatID_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "FFFFBFFRLR",
            "FFFFBFFRRL",
            "FFFFBFBLLL",
            "FFFFBFBLLR",
        };

        Assert::AreEqual(39, CurrentDay::missingSeatID(lines));
    }

};
