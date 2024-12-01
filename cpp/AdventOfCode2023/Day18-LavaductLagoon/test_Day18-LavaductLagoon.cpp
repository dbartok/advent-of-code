#include "Day18-LavaductLagoon.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day18;

TEST_CLASS(Day18LavaductLagoon)
{
public:

    TEST_METHOD(amountOfLavaHeld_SimpleTests)
    {
        Assert::AreEqual(62ll, CurrentDay::amountOfLavaHeld(m_lines));
    }

    TEST_METHOD(amountOfLavaHeldWithSwappedInstructions_SimpleTests)
    {
        Assert::AreEqual(952408144115ll, CurrentDay::amountOfLavaHeldWithSwappedInstructions(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "R 6 (#70c710)",
        "D 5 (#0dc571)",
        "L 2 (#5713f0)",
        "D 2 (#d2c081)",
        "R 2 (#59c680)",
        "D 2 (#411b91)",
        "L 5 (#8ceee2)",
        "U 2 (#caa173)",
        "L 1 (#1b58a2)",
        "U 2 (#caa171)",
        "R 2 (#7807d2)",
        "U 3 (#a77fa3)",
        "L 2 (#015232)",
        "U 2 (#7a21e3)"
    };
};
