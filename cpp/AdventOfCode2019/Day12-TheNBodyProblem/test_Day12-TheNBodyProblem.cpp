#include "Day12-TheNBodyProblem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day12;

TEST_CLASS(Day12TheNBodyProblem)
{
public:

    TEST_METHOD(totalEnergyAfterSteps_SimpleTests)
    {

        Assert::AreEqual(179, CurrentDay::totalEnergyAfterSteps(m_positions1, 10));
        Assert::AreEqual(1940, CurrentDay::totalEnergyAfterSteps(m_positions2, 100));
    }

    TEST_METHOD(numStepsUntilRepetition_SimpleTests)
    {

        Assert::AreEqual(2772ull, CurrentDay::numStepsUntilRepetition(m_positions1));
        Assert::AreEqual(4686774924ull, CurrentDay::numStepsUntilRepetition(m_positions2));
    }

private:
    const std::vector<std::string> m_positions1 =
    {
        "<x=-1, y=0, z=2>",
        "<x=2, y=-10, z=-7>",
        "<x=4, y=-8, z=8>",
        "<x=3, y=5, z=-1>"
    };

    const std::vector<std::string> m_positions2 =
    {
        "<x=-8, y=-10, z=0>",
        "<x=5, y=5, z=10>",
        "<x=2, y=-7, z=3>",
        "<x=9, y=-8, z=-3>"
    };
};
