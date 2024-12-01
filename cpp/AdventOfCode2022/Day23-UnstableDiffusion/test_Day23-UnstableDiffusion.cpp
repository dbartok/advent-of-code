#include "Day23-UnstableDiffusion.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day23;

TEST_CLASS(Day23UnstableDiffusion)
{
public:

    TEST_METHOD(numGroundTilesInBoundingRectangle_SimpleTests)
    {
        Assert::AreEqual(110u, CurrentDay::numGroundTilesInBoundingRectangle(m_lines));
    }

    TEST_METHOD(numFirstRoundWhereNoElfMoves_SimpleTests)
    {
        Assert::AreEqual(20u, CurrentDay::numFirstRoundWhereNoElfMoves(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "....#..",
        "..###.#",
        "#...#.#",
        ".#...##",
        "#.###..",
        "##.#.##",
        ".#..#.."
    };
};
