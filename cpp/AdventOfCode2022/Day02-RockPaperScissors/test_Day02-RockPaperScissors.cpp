//TODO: Rename to current day and name of the puzzle
#include "Day02-RockPaperScissors.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day02;

TEST_CLASS(Day02RockPaperScissors)
{
public:

    TEST_METHOD(totalScoreAccordingToStrategyGuide_SimpleTests)
    {
        Assert::AreEqual(15, CurrentDay::totalScoreAccordingToStrategyGuide(m_lines));
    }

    TEST_METHOD(totalScoreAccordingToElfInstructions_SimpleTests)
    {
        Assert::AreEqual(12, CurrentDay::totalScoreAccordingToElfInstructions(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "A Y",
        "B X",
        "C Z"
    };
};
