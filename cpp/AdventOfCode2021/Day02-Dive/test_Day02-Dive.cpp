#include "Day02-Dive.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day02;

TEST_CLASS(Day02Dive)
{
public:

    TEST_METHOD(finalHorizontalPositionAndDepthMultiplied_SimpleTests)
    {
        Assert::AreEqual(150, CurrentDay::finalHorizontalPositionAndDepthMultiplied(instructions));
    }

    TEST_METHOD(finalHorizontalPositionAndDepthMultipliedWithAdjustedCourse_SimpleTests)
    {
        Assert::AreEqual(900, CurrentDay::finalHorizontalPositionAndDepthMultipliedWithAdjustedCourse(instructions));
    }

private:
    const std::vector<std::string> instructions =
    {
        "forward 5",
        "down 5",
        "forward 8",
        "up 3",
        "down 8",
        "forward 2"
    };
};
