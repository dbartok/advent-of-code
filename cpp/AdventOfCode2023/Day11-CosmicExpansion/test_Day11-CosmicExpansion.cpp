#include "Day11-CosmicExpansion.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day11;

TEST_CLASS(Day11CosmicExpansion)
{
public:

    TEST_METHOD(sumOfShortestPathsBetweenAllPairs_SimpleTests)
    {
        Assert::AreEqual(374ll, CurrentDay::sumOfShortestPathsBetweenAllPairs(m_lines));
    }

    TEST_METHOD(sumOfShortestPathsBetweenAllPairsWithLargerExpansionRate_SimpleTests)
    {
        Assert::AreEqual(1030ll, CurrentDay::sumOfShortestPathsBetweenAllPairsWithLargerExpansionRate(m_lines, 10));
        Assert::AreEqual(8410ll, CurrentDay::sumOfShortestPathsBetweenAllPairsWithLargerExpansionRate(m_lines, 100));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "...#......",
        ".......#..",
        "#.........",
        "..........",
        "......#...",
        ".#........",
        ".........#",
        "..........",
        ".......#..",
        "#...#....."
    };
};
