#include "Day13-PointOfIncidence.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day13;

TEST_CLASS(Day13PointOfIncidence)
{
public:

    TEST_METHOD(numberAfterSummarizingAllNotes_SimpleTests)
    {
        Assert::AreEqual(405, CurrentDay::numberAfterSummarizingAllNotes(m_lines));
    }

    TEST_METHOD(numberAfterSummarizingAllNotesWithSmudge_SimpleTests)
    {
        Assert::AreEqual(400, CurrentDay::numberAfterSummarizingAllNotesWithSmudge(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "#.##..##.",
        "..#.##.#.",
        "##......#",
        "##......#",
        "..#.##.#.",
        "..##..##.",
        "#.#.##.#.",
        "",
        "#...##..#",
        "#....#..#",
        "..##..###",
        "#####.##.",
        "#####.##.",
        "..##..###",
        "#....#..#"
    };
};
