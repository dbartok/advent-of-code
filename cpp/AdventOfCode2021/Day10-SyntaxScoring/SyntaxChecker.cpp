#include "SyntaxChecker.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cassert>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const std::unordered_map<char, int> CHARACTER_TO_ERROR_SCORE =
{
    {')', 3},
    {']', 57},
    {'}', 1197},
    {'>', 25137}
};

const std::unordered_map<char, int> CHARACTER_TO_AUTOCOMPLETE_SCORE =
{
    {'(', 1},
    {'[', 2},
    {'{', 3},
    {'<', 4}
};

const std::unordered_map<char, char> CLOSING_TO_OPENING =
{
    {']', '['},
    {')', '('},
    {'}', '{'},
    {'>', '<'}
};

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day10
{

SyntaxChecker::SyntaxChecker(std::string line)
    : m_line{std::move(line)}
{

}

int SyntaxChecker::calculateErrorScore() const
{
    m_openBrackets = {};

    for (const char c : m_line)
    {
        const auto openingCounterpartIter = CLOSING_TO_OPENING.find(c);

        // This is an opening bracket
        if (openingCounterpartIter == CLOSING_TO_OPENING.cend())
        {
            m_openBrackets.push(c);
        }
        // This is a closing bracket
        else
        {
            if (m_openBrackets.empty() || m_openBrackets.top() != openingCounterpartIter->second)
            {
                return CHARACTER_TO_ERROR_SCORE.at(c);
            }
            m_openBrackets.pop();
        }
    }

    return 0;
}

int64_t SyntaxChecker::getAutocompleteScore() const
{
    const int errorScore = calculateErrorScore();
    assert(errorScore == 0);

    int64_t autocompleteScore = 0;

    while (!m_openBrackets.empty())
    {
        const char c = m_openBrackets.top();
        autocompleteScore *= 5;
        autocompleteScore += CHARACTER_TO_AUTOCOMPLETE_SCORE.at(c);

        m_openBrackets.pop();
    }

    return autocompleteScore;
}

}
}
}
