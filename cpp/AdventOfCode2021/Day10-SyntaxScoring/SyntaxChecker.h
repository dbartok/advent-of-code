#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stack>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day10
{

class SyntaxChecker
{
public:
    SyntaxChecker(std::string line);

    int calculateErrorScore() const;
    int64_t getAutocompleteScore() const;

private:
    std::string m_line;
    mutable std::stack<char> m_openBrackets;
};

}
}
}
