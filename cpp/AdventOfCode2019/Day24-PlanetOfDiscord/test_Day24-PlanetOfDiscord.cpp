#include "Day24-PlanetOfDiscord.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day24;

TEST_CLASS(Day24PlanetOfDiscord)
{
public:

    TEST_METHOD(biodiversityRatingOfFirstDuplicateLayout_SimpleTests)
    {
        std::vector<std::string> initialLayout =
        {
            "....#",
            "#..#.",
            "#..##",
            "..#..",
            "#...."
        };

        Assert::AreEqual(2129920, CurrentDay::biodiversityRatingOfFirstDuplicateLayout(m_initialLayout));
    }

    TEST_METHOD(numBugsAfterSimulationRecursiveGrid_SimpleTests)
    {
        Assert::AreEqual(99u, CurrentDay::numBugsAfterSimulationRecursiveGrid(m_initialLayout, 10));
    }

private:
    std::vector<std::string> m_initialLayout =
    {
        "....#",
        "#..#.",
        "#..##",
        "..#..",
        "#...."
    };
};
