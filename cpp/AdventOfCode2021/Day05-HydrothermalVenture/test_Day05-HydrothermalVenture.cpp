#include "Day05-HydrothermalVenture.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day05;

TEST_CLASS(Day05HydrothermalVenture)
{
public:

    TEST_METHOD(numPointsWhereHorizontalOrVerticalLinesOverlap_SimpleTests)
    {
        Assert::AreEqual(5, CurrentDay::numPointsWhereHorizontalOrVerticalLinesOverlap(m_lines));
    }

    TEST_METHOD(numPointsWhereLinesOverlap_SimpleTests)
    {
        Assert::AreEqual(12, CurrentDay::numPointsWhereLinesOverlap(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "0,9 -> 5,9",
        "8,0 -> 0,8",
        "9,4 -> 3,4",
        "2,2 -> 2,1",
        "7,0 -> 7,4",
        "6,4 -> 2,0",
        "0,9 -> 2,9",
        "3,4 -> 1,4",
        "0,0 -> 8,8",
        "5,5 -> 8,2"
    };
};
