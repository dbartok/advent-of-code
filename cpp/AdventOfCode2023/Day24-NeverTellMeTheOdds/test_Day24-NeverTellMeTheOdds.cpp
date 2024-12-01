#include "Day24-NeverTellMeTheOdds.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day24;

TEST_CLASS(Day24NeverTellMeTheOdds)
{
public:

    TEST_METHOD(numXYIntersectionsWithinTestArea_SimpleTests)
    {
        Assert::AreEqual(2, CurrentDay::numXYIntersectionsWithinTestArea(lines, 7, 27));
    }

    TEST_METHOD(sumOfCoordinatesOfIniitialRockPosition_SimpleTests)
    {
        Assert::AreEqual(47ll, CurrentDay::sumOfCoordinatesOfIniitialRockPosition(lines));
    }


private:
    const std::vector<std::string> lines =
    {
        "19, 13, 30 @ -2,  1, -2",
        "18, 19, 22 @ -1, -1, -2",
        "20, 25, 34 @ -2, -2, -4",
        "12, 31, 28 @ -1, -2, -1",
        "20, 19, 15 @  1, -5, -3"
    };
};
