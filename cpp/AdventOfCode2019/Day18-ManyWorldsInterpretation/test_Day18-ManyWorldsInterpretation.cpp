#include "Day18-ManyWorldsInterpretation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day18;

TEST_CLASS(Day18ManyWorldsInterpretation)
{
public:

    TEST_METHOD(lengthOfShortestPathWithAllKeys_SimpleTests)
    {
        std::vector<std::string> vault1 =
        {
            "#########",
            "#b.A.@.a#",
            "#########"
        };
        Assert::AreEqual(8, CurrentDay::lengthOfShortestPathWithAllKeys(vault1));

        std::vector<std::string> vault2 =
        {
            "########################",
            "#f.D.E.e.C.b.A.@.a.B.c.#",
            "######################.#",
            "#d.....................#",
            "########################"
        };
        Assert::AreEqual(86, CurrentDay::lengthOfShortestPathWithAllKeys(vault2));

        std::vector<std::string> vault3 =
        {
            "########################",
            "#...............b.C.D.f#",
            "#.######################",
            "#.....@.a.B.c.d.A.e.F.g#",
            "########################"
        };
        Assert::AreEqual(132, CurrentDay::lengthOfShortestPathWithAllKeys(vault3));

        std::vector<std::string> vault4 =
        {
            "#################",
            "#i.G..c...e..H.p#",
            "########.########",
            "#j.A..b...f..D.o#",
            "########@########",
            "#k.E..a...g..B.n#",
            "########.########",
            "#l.F..d...h..C.m#",
            "#################"
        };
        Assert::AreEqual(136, CurrentDay::lengthOfShortestPathWithAllKeys(vault4));

        std::vector<std::string> vault5 =
        {
            "########################",
            "#@..............ac.GI.b#",
            "###d#e#f################",
            "###A#B#C################",
            "###g#h#i################",
            "########################"
        };
        Assert::AreEqual(81, CurrentDay::lengthOfShortestPathWithAllKeys(vault5));
    }

    TEST_METHOD(lengthOfShortestPathWithAllKeysMultipleRobots_SimpleTests)
    {
        std::vector<std::string> vault1 =
        {
            "#######",
            "#a.#Cd#",
            "##...##",
            "##.@.##",
            "##...##",
            "#cB#Ab#",
            "#######"
        };
        Assert::AreEqual(8, CurrentDay::lengthOfShortestPathWithAllKeysMultipleRobots(vault1));

        std::vector<std::string> vault2 =
        {
            "###############",
            "#d.ABC.#.....a#",
            "######...######",
            "######.@.######",
            "######...######",
            "#b.....#.....c#",
            "###############"
        };
        Assert::AreEqual(24, CurrentDay::lengthOfShortestPathWithAllKeysMultipleRobots(vault2));
    }

};
