#include "Day08-TreetopTreeHouse.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day08;

TEST_CLASS(Day08TreetopTreeHouse)
{
public:

    TEST_METHOD(numTreesVisibleFromOutsideTheGrid_SimpleTests)
    {
        Assert::AreEqual(21, CurrentDay::numTreesVisibleFromOutsideTheGrid(m_lines));
    }

    TEST_METHOD(highestPossibleScenicScore_SimpleTests)
    {
        Assert::AreEqual(8, CurrentDay::highestPossibleScenicScore(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "30373",
        "25512",
        "65332",
        "33549",
        "35390"
    };
};
