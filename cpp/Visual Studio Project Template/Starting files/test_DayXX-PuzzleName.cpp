//TODO: Rename to current day and name of the puzzle
#include "DayXX-PuzzleName.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//TODO: Rename to current year and day
namespace CurrentDay = AdventOfCode::YearXXXX::DayXX;

//TODO: Rename to current day and name of the puzzle
TEST_CLASS(DayXXPuzzleName)
{
public:

    TEST_METHOD(solution1_SimpleTests)
    {
        Assert::AreEqual(101, CurrentDay::solution1(100));
        Assert::AreEqual(1002, CurrentDay::solution1(1001));
    }

    TEST_METHOD(solution2_SimpleTests)
    {
        Assert::AreEqual(102, CurrentDay::solution2(100));
        Assert::AreEqual(1003, CurrentDay::solution2(1001));
    }

};
