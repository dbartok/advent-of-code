#include "Day22-CrabCombat.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day22;

TEST_CLASS(Day22CrabCombat)
{
public:

    TEST_METHOD(winningPlayerScore_SimpleTests)
    {
        Assert::AreEqual(306, CurrentDay::winningPlayerScore(m_lines));
    }

    TEST_METHOD(winningPlayerScoreRecursiveCombat_SimpleTests)
    {
        Assert::AreEqual(291, CurrentDay::winningPlayerScoreRecursiveCombat(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "Player 1:",
        "9",
        "2",
        "6",
        "3",
        "1",
        "",
        "Player 2:",
        "5",
        "8",
        "4",
        "7",
        "10"
    };
};
