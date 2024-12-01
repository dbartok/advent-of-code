#include "Day16-ProboscideaVolcanium.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day16;

TEST_CLASS(Day16ProboscideaVolcanium)
{
public:

    TEST_METHOD(mostPressureThatCanBeReleased_SimpleTests)
    {
        Assert::AreEqual(1651, CurrentDay::mostPressureThatCanBeReleased(m_lines));
    }

    TEST_METHOD(mostPressureThatCanBeReleasedWorkingWithElephant_SimpleTests)
    {
        Assert::AreEqual(1707, CurrentDay::mostPressureThatCanBeReleasedWorkingWithElephant(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "Valve AA has flow rate=0; tunnels lead to valves DD, II, BB",
        "Valve BB has flow rate=13; tunnels lead to valves CC, AA",
        "Valve CC has flow rate=2; tunnels lead to valves DD, BB",
        "Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE",
        "Valve EE has flow rate=3; tunnels lead to valves FF, DD",
        "Valve FF has flow rate=0; tunnels lead to valves EE, GG",
        "Valve GG has flow rate=0; tunnels lead to valves FF, HH",
        "Valve HH has flow rate=22; tunnel leads to valve GG",
        "Valve II has flow rate=0; tunnels lead to valves AA, JJ",
        "Valve JJ has flow rate=21; tunnel leads to valve II"
    };
};
