#include "Day11-SeatingSystem.h"
#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day11;

TEST_CLASS(Day11SeatingSystem)
{
public:

    TEST_METHOD(numOccupiedSeatsWithAdjacencyRules_SimpleTests)
    {
        Assert::AreEqual(37, CurrentDay::numOccupiedSeatsWithAdjacencyRules(m_lines));
    }

    TEST_METHOD(numOccupiedSeatsWithVisibilityRules_SimpleTests)
    {
        Assert::AreEqual(26, CurrentDay::numOccupiedSeatsWithVisibilityRules(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "L.LL.LL.LL",
        "LLLLLLL.LL",
        "L.L.L..L..",
        "LLLL.LL.LL",
        "L.LL.LL.LL",
        "L.LLLLL.LL",
        "..L.L.....",
        "LLLLLLLLLL",
        "L.LLLLLL.L",
        "L.LLLLL.LL"
    };

};
