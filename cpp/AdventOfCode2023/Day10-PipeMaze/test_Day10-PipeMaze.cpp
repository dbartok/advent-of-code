#include "Day10-PipeMaze.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day10;

TEST_CLASS(Day10PipeMaze)
{
public:

    TEST_METHOD(numStepsAlongMainLoopToFarthestPosition_SimpleLoop)
    {
        const std::vector<std::string> lines =
        {
            "-L|F7",
            "7S-7|",
            "L|7||",
            "-L-J|",
            "L|-JF"
        };

        Assert::AreEqual(4, CurrentDay::numStepsAlongMainLoopToFarthestPosition(lines));
    }

    TEST_METHOD(numStepsAlongMainLoopToFarthestPosition_MoreComplexLoop)
    {
        const std::vector<std::string> lines =
        {
            "7-F7-",
            ".FJ|7",
            "SJLL7",
            "|F--J",
            "LJ.LJ"
        };

        Assert::AreEqual(8, CurrentDay::numStepsAlongMainLoopToFarthestPosition(lines));
    }

    TEST_METHOD(numTilesEnclosedByMainLoop_NoJunkPipes)
    {
        const std::vector<std::string> lines =
        {
            ".F----7F7F7F7F-7....",
            ".|F--7||||||||FJ....",
            ".||.FJ||||||||L7....",
            "FJL7L7LJLJ||LJ.L-7..",
            "L--J.L7...LJS7F-7L7.",
            "....F-J..F7FJ|L7L7L7",
            "....L7.F7||L7|.L7L7|",
            ".....|FJLJ|FJ|F7|.LJ",
            "....FJL-7.||.||||...",
            "....L---J.LJ.LJLJ..."
        };

        Assert::AreEqual(8, CurrentDay::numTilesEnclosedByMainLoop(lines));
    }

    TEST_METHOD(numTilesEnclosedByMainLoop_JunkPipes)
    {
        const std::vector<std::string> lines =
        {
            "FF7FSF7F7F7F7F7F---7",
            "L|LJ||||||||||||F--J",
            "FL-7LJLJ||||||LJL-77",
            "F--JF--7||LJLJ7F7FJ-",
            "L---JF-JLJ.||-FJLJJ7",
            "|F|F-JF---7F7-L7L|7|",
            "|FFJF7L7F-JF7|JL---7",
            "7-L-JL7||F7|L7F-7F7|",
            "L.L7LFJ|||||FJL7||LJ",
            "L7JLJL-JLJLJL--JLJ.L"
        };

        Assert::AreEqual(10, CurrentDay::numTilesEnclosedByMainLoop(lines));
    }
};
