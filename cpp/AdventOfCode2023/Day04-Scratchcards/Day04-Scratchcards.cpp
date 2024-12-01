#include "Day04-Scratchcards.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day04
{

using Numbers = std::vector<int>;
using Scratchcard = std::pair<Numbers, Numbers>;

Numbers parseNumbersSegment(std::string numbersSegment)
{
    boost::trim(numbersSegment);
    Numbers numbers;
    AdventOfCode::Utils::splitStringIntoTypedVector(numbersSegment, numbers);
    return numbers;
}

Scratchcard parseScratchcardLine(const std::string& scratchcardLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, scratchcardLine, boost::is_any_of(":|"));

    Numbers winningNumbers = parseNumbersSegment(tokens.at(1));
    Numbers playedNumbers = parseNumbersSegment(tokens.at(2));

    return {winningNumbers, playedNumbers};
}


std::vector<Scratchcard> parseScratchcardLines(const std::vector<std::string>& scratchcardLines)
{
    std::vector<Scratchcard> scratchcards;

    for (const auto& scratchcardLine : scratchcardLines)
    {
        Scratchcard scratchcard = parseScratchcardLine(scratchcardLine);
        scratchcards.push_back(std::move(scratchcard));
    }

    return scratchcards;
}

unsigned getNumMatchingNumbers(const Scratchcard& scratchcard)
{
    Numbers winningNumbers = scratchcard.first;
    std::sort(winningNumbers.begin(), winningNumbers.end());

    Numbers playedNumbers = scratchcard.second;
    std::sort(playedNumbers.begin(), playedNumbers.end());

    Numbers successfullyGuessedNumbers;
    std::set_intersection(winningNumbers.cbegin(), winningNumbers.cend(),
                          playedNumbers.cbegin(), playedNumbers.cend(),
                          std::back_inserter(successfullyGuessedNumbers));

    return successfullyGuessedNumbers.size();
}


int numPointsWorthInTotal(const std::vector<std::string>& scratchcardLines)
{
    const std::vector<Scratchcard> scratchcards = parseScratchcardLines(scratchcardLines);

    return std::accumulate(scratchcards.cbegin(), scratchcards.cend(), 0, [](int acc, const auto& scratchcard)
                           {
                               const unsigned numMatchingNumbers = getNumMatchingNumbers(scratchcard);
                               const int scoreExponent = std::max(numMatchingNumbers - 1, 0u);
                               const int currentScore = static_cast<int>(std::pow(2, scoreExponent));

                               return acc + currentScore;
                           });
}

int numTotalScratchcardsIncludingOriginalsAndCopies(const std::vector<std::string>& scratchcardLines)
{
    const std::vector<Scratchcard> scratchcards = parseScratchcardLines(scratchcardLines);

    std::vector<int> scratchcardIndexToQuantity(scratchcards.size(), 1);

    for (size_t scratchcardIndex = 0; scratchcardIndex < scratchcards.size(); ++scratchcardIndex)
    {
        const int score = getNumMatchingNumbers(scratchcards.at(scratchcardIndex));
        const int currentQuantity = scratchcardIndexToQuantity.at(scratchcardIndex);

        for (int copyOffset = 1; copyOffset <= score; ++copyOffset)
        {
            scratchcardIndexToQuantity.at(scratchcardIndex + copyOffset) += currentQuantity;
        }
    }

    return std::accumulate(scratchcardIndexToQuantity.cbegin(), scratchcardIndexToQuantity.cend(), 0);
}

}
}
}