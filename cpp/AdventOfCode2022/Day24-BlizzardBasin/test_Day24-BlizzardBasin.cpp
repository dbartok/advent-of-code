#include "Day24-BlizzardBasin.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day24;

TEST_CLASS(Day24BlizzardBasin)
{
public:

    TEST_METHOD(fewestNumberOfMinutesToReachGoal_SimpleTests)
    {
        Assert::AreEqual(18u, CurrentDay::fewestNumberOfMinutesToReachGoal(m_lines));
    }

    TEST_METHOD(fewestNumberOfMinutesToReachGoalAfterGoingBackForSnacks_SimpleTests)
    {
        Assert::AreEqual(54u, CurrentDay::fewestNumberOfMinutesToReachGoalAfterGoingBackForSnacks(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "#.######",
        "#>>.<^<#",
        "#.<..<<#",
        "#>v.><>#",
        "#<^v^^>#",
        "######.#"
    };
};
