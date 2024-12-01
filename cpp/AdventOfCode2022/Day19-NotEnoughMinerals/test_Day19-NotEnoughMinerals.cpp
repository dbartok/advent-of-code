#include "Day19-NotEnoughMinerals.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day19;

TEST_CLASS(Day19NotEnoughMinerals)
{
public:

    TEST_METHOD(sumOfBlueprintQualityLevels_SimpleTests)
    {
        Assert::AreEqual(33, CurrentDay::sumOfBlueprintQualityLevels(m_lines));
    }

    TEST_METHOD(productOfFirstFewBlueprintMaxGeodesWithMoreTime_SimpleTests)
    {
        Assert::AreEqual(56 * 62, CurrentDay::productOfFirstFewBlueprintMaxGeodesWithMoreTime(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "Blueprint 1: Each ore robot costs 4 ore. Each clay robot costs 2 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 2 ore and 7 obsidian.",
        "Blueprint 2: Each ore robot costs 2 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 8 clay. Each geode robot costs 3 ore and 12 obsidian."
    };
};
