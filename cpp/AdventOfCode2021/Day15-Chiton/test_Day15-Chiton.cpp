#include "Day15-Chiton.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day15;

TEST_CLASS(Day15Chiton)
{
public:

    TEST_METHOD(lowestTotalRiskOfAnyPath_SimpleTests)
    {
        Assert::AreEqual(40, CurrentDay::lowestTotalRiskOfAnyPath(m_lines));
    }

    TEST_METHOD(lowestTotalRiskOfAnyPathRepeatedMap_SimpleTests)
    {
        Assert::AreEqual(315, CurrentDay::lowestTotalRiskOfAnyPathRepeatedMap(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "1163751742",
        "1381373672",
        "2136511328",
        "3694931569",
        "7463417111",
        "1319128137",
        "1359912421",
        "3125421639",
        "1293138521",
        "2311944581"
    };
};
