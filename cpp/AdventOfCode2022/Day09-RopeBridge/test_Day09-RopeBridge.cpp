#include "Day09-RopeBridge.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day09;

TEST_CLASS(Day09RopeBridge)
{
public:

    TEST_METHOD(numPositionsVisitedByTail_SimpleTests)
    {
        const std::vector<std::string>& lines =
        {
            "R 4",
            "U 4",
            "L 3",
            "D 1",
            "R 4",
            "D 1",
            "L 5",
            "R 2"
        };

        Assert::AreEqual(13, CurrentDay::numPositionsVisitedByTail(lines));
    }

    TEST_METHOD(numPositionsVisitedByTailWithLongerRope_SimpleTests)
    {
        const std::vector<std::string>& lines =
        {
            "R 5",
            "U 8",
            "L 8",
            "D 3",
            "R 17",
            "D 10",
            "L 25",
            "U 20"
        };

        Assert::AreEqual(36, CurrentDay::numPositionsVisitedByTailWithLongerRope(lines));
    }

};
