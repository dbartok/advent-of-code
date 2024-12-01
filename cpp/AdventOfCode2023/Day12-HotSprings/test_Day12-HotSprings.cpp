#include "Day12-HotSprings.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day12;

TEST_CLASS(Day12HotSprings)
{
public:

    TEST_METHOD(sumOfAllPossibleArrangements_SimpleTests)
    {
        Assert::AreEqual(21ll, CurrentDay::sumOfAllPossibleArrangements(m_lines));
    }

    TEST_METHOD(sumOfAllPossibleArrangementsUnfolded_SimpleTests)
    {
        Assert::AreEqual(525152ll, CurrentDay::sumOfAllPossibleArrangementsUnfolded(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "???.### 1,1,3",
        ".??..??...?##. 1,1,3",
        "?#?#?#?#?#?#?#? 1,3,1,6",
        "????.#...#... 4,1,1",
        "????.######..#####. 1,6,5",
        "?###???????? 3,2,1"
    };
};
