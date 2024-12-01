#include "Day11-MonkeyInTheMiddle.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day11;

TEST_CLASS(Day11MonkeyInTheMiddle)
{
public:

    TEST_METHOD(levelOfMonkeyBusiness_SimpleTests)
    {
        Assert::AreEqual(10605ll, CurrentDay::levelOfMonkeyBusiness(m_lines));
    }

    TEST_METHOD(levelOfMonkeyBusinessWithRidiculousWorryLevels_SimpleTests)
    {
        Assert::AreEqual(2713310158ll, CurrentDay::levelOfMonkeyBusinessWithRidiculousWorryLevels(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "Monkey 0:",
        "  Starting items: 79, 98",
        "  Operation: new = old * 19",
        "  Test: divisible by 23",
        "    If true: throw to monkey 2",
        "    If false: throw to monkey 3",
        "",
        "Monkey 1:",
        "  Starting items: 54, 65, 75, 74",
        "  Operation: new = old + 6",
        "  Test: divisible by 19",
        "    If true: throw to monkey 2",
        "    If false: throw to monkey 0",
        "",
        "Monkey 2:",
        "  Starting items: 79, 60, 97",
        "  Operation: new = old * old",
        "  Test: divisible by 13",
        "    If true: throw to monkey 1",
        "    If false: throw to monkey 3",
        "",
        "Monkey 3:",
        "  Starting items: 74",
        "  Operation: new = old + 3",
        "  Test: divisible by 17",
        "    If true: throw to monkey 0",
        "    If false: throw to monkey 1"
    };
};
