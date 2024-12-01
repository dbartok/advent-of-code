#include "Day02-CubeConundrum.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day02;

TEST_CLASS(Day02CubeConundrum)
{
public:

    TEST_METHOD(sumOfIDsOfPossibleGames_SimpleTests)
    {
        Assert::AreEqual(8, CurrentDay::sumOfIDsOfPossibleGames(m_lines));
    }

    TEST_METHOD(sumOfPowerOfMinimalSets_SimpleTests)
    {
        Assert::AreEqual(2286, CurrentDay::sumOfPowerOfMinimalSets(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
        "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
        "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red",
        "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red",
        "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"
    };
};
