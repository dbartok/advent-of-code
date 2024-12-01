#include "Day22-MonkeyMap.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day22;

TEST_CLASS(Day22MonkeyMap)
{
public:

    TEST_METHOD(finalPassword_SimpleTests)
    {
        Assert::AreEqual(6032, CurrentDay::finalPassword(lines));
    }

    TEST_METHOD(finalPasswordWithCubeMap_SimpleTests)
    {
        Assert::AreEqual(5031, CurrentDay::finalPasswordWithCubeMap(lines, 4));
    }

private:
    const std::vector<std::string> lines =
    {
        "        ...#",
        "        .#..",
        "        #...",
        "        ....",
        "...#.......#",
        "........#...",
        "..#....#....",
        "..........#.",
        "        ...#....",
        "        .....#..",
        "        .#......",
        "        ......#.",
        "",
        "10R5L5R10L4R5L5",
    };
};
