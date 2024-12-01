#include "Day25-SeaCucumber.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day25;

TEST_CLASS(Day25SeaCucumber)
{
public:

    TEST_METHOD(firstStepWithoutAnyMovement_SimpleTests)
    {
        const std::vector<std::string> lines =
        {
            "v...>>.vv>",
            ".vv>>.vv..",
            ">>.>v>...v",
            ">>v>>.>.v.",
            "v>v.vv.v..",
            ">.>>..v...",
            ".vv..>.>v.",
            "v.v..>>v.v",
            "....v..v.>"
        };

        Assert::AreEqual(58u, CurrentDay::firstStepWithoutAnyMovement(lines));
    }

};
