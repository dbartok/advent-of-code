#include "Day10-SyntaxScoring.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day10;

TEST_CLASS(Day10SyntaxScoring)
{
public:

    TEST_METHOD(totalSyntaxErrorScore_SimpleTests)
    {
        Assert::AreEqual(26397, CurrentDay::totalSyntaxErrorScore(m_lines));
    }

    TEST_METHOD(middleAutocompleteScore_SimpleTests)
    {
        Assert::AreEqual(288957ll, CurrentDay::middleAutocompleteScore(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "[({(<(())[]>[[{[]{<()<>>",
        "[(()[<>])]({[<{<<[]>>(",
        "{([(<{}[<>[]}>{[]{[(<()>",
        "(((({<>}<{<{<>}{[]{[]{}",
        "[[<[([]))<([[{}[[()]]]",
        "[{[{({}]{}}([{[{{{}}([]",
        "{<[[]]>}<{[{[{[]{()[[[]",
        "[<(<(<(<{}))><([]([]()",
        "<{([([[(<>()){}]>(<<{{",
        "<{([{{}}[<[[[<>{}]]]>[]]"
    };

};
