#include "Day10-SyntaxScoring.h"

#include "SyntaxChecker.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day10
{

std::vector<SyntaxChecker> createSyntaxCheckers(const std::vector<std::string>& syntaxLines)
{
    std::vector<SyntaxChecker> syntaxCheckers;

    for (const auto& line : syntaxLines)
    {
        syntaxCheckers.emplace_back(line);
    }

    return syntaxCheckers;
}


int totalSyntaxErrorScore(const std::vector<std::string>& syntaxLines)
{
    const std::vector<SyntaxChecker> syntaxCheckers = createSyntaxCheckers(syntaxLines);
    return std::accumulate(syntaxCheckers.cbegin(), syntaxCheckers.cend(), 0, [](const auto& acc, const auto& syntaxChecker)
                           {
                               return acc + syntaxChecker.calculateErrorScore();
                           });
}

int64_t middleAutocompleteScore(const std::vector<std::string>& syntaxLines)
{
    std::vector<SyntaxChecker> syntaxCheckers = createSyntaxCheckers(syntaxLines);
    syntaxCheckers.erase(std::remove_if(syntaxCheckers.begin(),
                                        syntaxCheckers.end(),
                                        [](const auto& syntaxChecker)
                                        {
                                            return syntaxChecker.calculateErrorScore() > 0;
                                        }),
                         syntaxCheckers.end());

    std::sort(syntaxCheckers.begin(), syntaxCheckers.end(), [](const auto& lhs, const auto& rhs)
              {
                  return lhs.getAutocompleteScore() < rhs.getAutocompleteScore();
              });

    return syntaxCheckers.at(syntaxCheckers.size() / 2).getAutocompleteScore();
}

}
}
}