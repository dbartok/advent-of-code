#include "Day24-ImmuneSystemSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day24;

TEST_CLASS(Day24ImmuneSystemSimulator)
{
public:

    TEST_METHOD(numUnitsOfWinningArmy_SimpleTests)
    {
        Assert::AreEqual(5216u, CurrentDay::numUnitsOfWinningArmy(m_lines));
    }

    TEST_METHOD(numUnitsImmuneSystemSmallestBoost_SimpleTests)
    {
        Assert::AreEqual(51u, CurrentDay::numUnitsImmuneSystemSmallestBoost(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "Immune System:",
        "17 units each with 5390 hit points (weak to radiation, bludgeoning) with an attack that does 4507 fire damage at initiative 2",
        "989 units each with 1274 hit points (immune to fire; weak to bludgeoning, slashing) with an attack that does 25 slashing damage at initiative 3",
        "",
        "Infection:",
        "801 units each with 4706 hit points (weak to radiation) with an attack that does 116 bludgeoning damage at initiative 1",
        "4485 units each with 2961 hit points (immune to radiation; weak to fire, cold) with an attack that does 12 slashing damage at initiative 4"
    };

};
