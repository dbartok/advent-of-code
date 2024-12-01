#include "Day12-SubterraneanSustainability.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day12;

TEST_CLASS(Day12SubterraneanSustainability)
{
public:

    TEST_METHOD(sumOfPotNumbersWithPlantAfterGrowthShortTime_SimpleTests)
    {
        Assert::AreEqual(325ll, CurrentDay::sumOfPotNumbersWithPlantAfterGrowthShortTime(m_initialStateLine, m_neighborPatternLines));
    }

    TEST_METHOD(sumOfPotNumbersWithPlantAfterGrowthLongTime_SimpleTests)
    {
        Assert::AreEqual(999999999374ll, CurrentDay::sumOfPotNumbersWithPlantAfterGrowthLongTime(m_initialStateLine, m_neighborPatternLines));
    }

private:
    std::string m_initialStateLine = "initial state: #..#.#..##......###...###";

    std::vector<std::string> m_neighborPatternLines =
    {
        "...## => #",
        "..#.. => #",
        ".#... => #",
        ".#.#. => #",
        ".#.## => #",
        ".##.. => #",
        ".#### => #",
        "#.#.# => #",
        "#.### => #",
        "##.#. => #",
        "##.## => #",
        "###.. => #",
        "###.# => #",
        "####. => #"
    };
};
