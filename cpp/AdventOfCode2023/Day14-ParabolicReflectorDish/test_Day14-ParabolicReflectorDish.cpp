#include "Day14-ParabolicReflectorDish.h"
#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day14;

TEST_CLASS(Day14ParabolicReflectorDish)
{
public:

    TEST_METHOD(totalLoadOnNorthSupportBeamsAfterNorthSlide_SimpleTests)
    {
        Assert::AreEqual(136, CurrentDay::totalLoadOnNorthSupportBeamsAfterNorthSlide(m_lines));
    }

    TEST_METHOD(totalLoadOnNorthSupportBeamsAfterSeveralCycles_SimpleTests)
    {
        Assert::AreEqual(64, CurrentDay::totalLoadOnNorthSupportBeamsAfterSeveralCycles(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "O....#....",
        "O.OO#....#",
        ".....##...",
        "OO.#O....O",
        ".O.....O#.",
        "O.#..O.#.#",
        "..O..#O..O",
        ".......O..",
        "#....###..",
        "#OO..#...."
    };
};
