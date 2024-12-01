#include "Day08-HauntedWasteland.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day08;

TEST_CLASS(Day08HauntedWasteland)
{
public:

    TEST_METHOD(numStepsRequiredToReachEndpoint_ShortRoute)
    {
        const std::vector<std::string> lines =
        {
            "RL",
            "",
            "AAA = (BBB, CCC)",
            "BBB = (DDD, EEE)",
            "CCC = (ZZZ, GGG)",
            "DDD = (DDD, DDD)",
            "EEE = (EEE, EEE)",
            "GGG = (GGG, GGG)",
            "ZZZ = (ZZZ, ZZZ)"
        };

        Assert::AreEqual(2ll, CurrentDay::numStepsRequiredToReachEndpoint(lines));
    }

    TEST_METHOD(numStepsRequiredToReachEndpoint_LongerRoute)
    {
        const std::vector<std::string> lines =
        {
            "LLR",
            "",
            "AAA = (BBB, BBB)",
            "BBB = (AAA, ZZZ)",
            "ZZZ = (ZZZ, ZZZ)"
        };

        Assert::AreEqual(6ll, CurrentDay::numStepsRequiredToReachEndpoint(lines));
    }

    TEST_METHOD(numStepsRequiredToReachAllEndpointsSimultaneously_SimpleTests)
    {
        const std::vector<std::string> lines =
        {
            "LR",
            "",
            "11A = (11B, XXX)",
            "11B = (XXX, 11Z)",
            "11Z = (11B, XXX)",
            "22A = (22B, XXX)",
            "22B = (22C, 22C)",
            "22C = (22Z, 22Z)",
            "22Z = (22B, 22B)",
            "XXX = (XXX, XXX)"
        };

        Assert::AreEqual(6ll, CurrentDay::numStepsRequiredToReachAllEndpointsSimultaneously(lines));
    }
};
