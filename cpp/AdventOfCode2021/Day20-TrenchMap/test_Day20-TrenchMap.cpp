#include "Day20-TrenchMap.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day20;

TEST_CLASS(Day20TrenchMap)
{
public:

    TEST_METHOD(numPixelsLitAfterSmallEnhancement_SimpleTests)
    {
        Assert::AreEqual(35u, CurrentDay::numPixelsLitAfterSmallEnhancement(m_lines));
    }

    TEST_METHOD(numPixelsLitAfterLargeEnhancement_SimpleTests)
    {
        Assert::AreEqual(3351u, CurrentDay::numPixelsLitAfterLargeEnhancement(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..###..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#..#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#......#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.....####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.......##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#",
        "",
        "#..#.",
        "#....",
        "##..#",
        "..#..",
        "..###",
    };
};
