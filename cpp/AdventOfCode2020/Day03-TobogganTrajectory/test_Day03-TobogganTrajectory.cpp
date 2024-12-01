#include "Day03-TobogganTrajectory.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day03;

TEST_CLASS(Day03TobogganTrajectory)
{
public:

    TEST_METHOD(numTreesEncounteredSingleSlope_SimpleTests)
    {
        Assert::AreEqual(7ll, CurrentDay::numTreesEncounteredSingleSlope(m_lines));
    }

    TEST_METHOD(numTreesEncounteredMultipleSlopes_SimpleTests)
    {
        Assert::AreEqual(336ll, CurrentDay::numTreesEncounteredMultipleSlopes(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "..##.......",
        "#...#...#..",
        ".#....#..#.",
        "..#.#...#.#",
        ".#...##..#.",
        "..#.##.....",
        ".#.#.#....#",
        ".#........#",
        "#.##...#...",
        "#...##....#",
        ".#..#...#.#"
    };
};
