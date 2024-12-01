#include "Day21-MonkeyMath.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day21;

TEST_CLASS(Day21MonkeyMath)
{
public:

    TEST_METHOD(numberYelledByRootMonkey_SimpleTests)
    {
        Assert::AreEqual(152ll, CurrentDay::numberYelledByRootMonkey(m_lines));
    }

    TEST_METHOD(numberYelledByHumanToPassEqualityTest_SimpleTests)
    {
        Assert::AreEqual(301ll, CurrentDay::numberYelledByHumanToPassEqualityTest(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "root: pppw + sjmn",
        "dbpl: 5",
        "cczh: sllz + lgvd",
        "zczc: 2",
        "ptdq: humn - dvpt",
        "dvpt: 3",
        "lfqf: 4",
        "humn: 5",
        "ljgn: 2",
        "sjmn: drzm * dbpl",
        "sllz: 4",
        "pppw: cczh / lfqf",
        "lgvd: ljgn * ptdq",
        "drzm: hmdt - zczc",
        "hmdt: 32"
    };
};
