#include "Day17-ReservoirResearch.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day17;

TEST_CLASS(Day17ReservoirResearch)
{
public:

    TEST_METHOD(numTilesWaterCanReach_SimpleTests)
    {
        Assert::AreEqual(57u, CurrentDay::numTilesWaterCanReach(m_lines));
    }

    TEST_METHOD(numTilesWaterRetained_SimpleTests)
    {
        Assert::AreEqual(29u, CurrentDay::numTilesWaterRetained(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "x=495, y=2..7",
        "y=7, x=495..501",
        "x=501, y=3..7",
        "x=498, y=2..4",
        "x=506, y=1..2",
        "x=498, y=10..13",
        "x=504, y=10..13",
        "y=13, x=498..504"
    };
};
