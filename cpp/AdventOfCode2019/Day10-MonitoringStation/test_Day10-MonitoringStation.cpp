#include "Day10-MonitoringStation.h"

#include <AdventOfCodeCommon/UnittestExtraDefinitions.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day10;

TEST_CLASS(Day10MonitoringStation)
{
public:

    TEST_METHOD(maxNumAsteroidsDetected_SimpleTests)
    {
        const std::vector<std::string> map1 =
        {
            ".#..#",
            ".....",
            "#####",
            "....#",
            "...##"
        };
        Assert::AreEqual(8u, CurrentDay::maxNumAsteroidsDetected(map1));

        const std::vector<std::string> map2 =
        {
            "......#.#.",
            "#..#.#....",
            "..#######.",
            ".#.#.###..",
            ".#..#.....",
            "..#....#.#",
            "#..#....#.",
            ".##.#..###",
            "##...#..#.",
            ".#....####"
        };
        Assert::AreEqual(33u, CurrentDay::maxNumAsteroidsDetected(map2));

        const std::vector<std::string> map3 =
        {
            "#.#...#.#.",
            ".###....#.",
            ".#....#...",
            "##.#.#.#.#",
            "....#.#.#.",
            ".##..###.#",
            "..#...##..",
            "..##....##",
            "......#...",
            ".####.###."
        };
        Assert::AreEqual(35u, CurrentDay::maxNumAsteroidsDetected(map3));

        const std::vector<std::string> map4 =
        {
            ".#..#..###",
            "####.###.#",
            "....###.#.",
            "..###.##.#",
            "##.##.#.#.",
            "....###..#",
            "..#.#..#.#",
            "#..#.#.###",
            ".##...##.#",
            ".....#.#.."
        };
        Assert::AreEqual(41u, CurrentDay::maxNumAsteroidsDetected(map4));

        Assert::AreEqual(210u, CurrentDay::maxNumAsteroidsDetected(large_map));
    }

    TEST_METHOD(vaporizationOrder_SimpleTests)
    {
        auto vaporizationOrder = CurrentDay::vaporizationOrder(large_map);

        auto dummy = CurrentDay::Coordinates{0, 0};
        vaporizationOrder.insert(vaporizationOrder.begin(), dummy);

        Assert::AreEqual(CurrentDay::Coordinates{11, 12}, vaporizationOrder.at(1));
        Assert::AreEqual(CurrentDay::Coordinates{12, 1}, vaporizationOrder.at(2));
        Assert::AreEqual(CurrentDay::Coordinates{12, 2}, vaporizationOrder.at(3));
        Assert::AreEqual(CurrentDay::Coordinates{12, 8}, vaporizationOrder.at(10));
        Assert::AreEqual(CurrentDay::Coordinates{16, 0}, vaporizationOrder.at(20));
        Assert::AreEqual(CurrentDay::Coordinates{16, 9}, vaporizationOrder.at(50));
        Assert::AreEqual(CurrentDay::Coordinates{10, 16}, vaporizationOrder.at(100));
        Assert::AreEqual(CurrentDay::Coordinates{9, 6}, vaporizationOrder.at(199));
        Assert::AreEqual(CurrentDay::Coordinates{8, 2}, vaporizationOrder.at(200));
        Assert::AreEqual(CurrentDay::Coordinates{10, 9}, vaporizationOrder.at(201));
        Assert::AreEqual(CurrentDay::Coordinates{11, 1}, vaporizationOrder.at(299));
    }

private:
    const std::vector<std::string> large_map =
    {
        ".#..##.###...#######",
        "##.############..##.",
        ".#.######.########.#",
        ".###.#######.####.#.",
        "#####.##.#.##.###.##",
        "..#####..#.#########",
        "####################",
        "#.####....###.#.#.##",
        "##.#################",
        "#####.##.###..####..",
        "..######..##.#######",
        "####.##.####...##..#",
        ".#####..#.######.###",
        "##...#.##########...",
        "#.##########.#######",
        ".####.#.###.###.#.##",
        "....##.##.###..#####",
        ".#.#.###########.###",
        "#.#.#.#####.####.###",
        "###.##.####.##.#..##"
    };

};
