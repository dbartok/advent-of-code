#include "Day07-CamelCards.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day07;

TEST_CLASS(Day07CamelCards)
{
public:

    TEST_METHOD(totalWinnings_SimpleTests)
    {
        Assert::AreEqual(6440, CurrentDay::totalWinnings(m_lines));
    }

    TEST_METHOD(totalWinningsWithJokers_SimpleTests)
    {
        Assert::AreEqual(5905, CurrentDay::totalWinningsWithJokers(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "32T3K 765",
        "T55J5 684",
        "KK677 28",
        "KTJJT 220",
        "QQQJA 483"
    };
};
