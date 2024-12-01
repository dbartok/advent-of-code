#include "Day04-CampCleanup.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day04;

TEST_CLASS(Day04CampCleanup)
{
public:

    TEST_METHOD(numAssignmentPairsFullyContainingEachOther_SimpleTests)
    {
        Assert::AreEqual(2, CurrentDay::numAssignmentPairsFullyContainingEachOther(m_lines));
    }

    TEST_METHOD(numAssignmentPairsOverlapping_SimpleTests)
    {
        Assert::AreEqual(4, CurrentDay::numAssignmentPairsOverlapping(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "2-4,6-8",
        "2-3,4-5",
        "5-7,7-9",
        "2-8,3-7",
        "6-6,4-6",
        "2-6,4-8"
    };
};
