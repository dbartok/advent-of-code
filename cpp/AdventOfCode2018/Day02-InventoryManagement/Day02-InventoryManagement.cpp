#include "Day02-InventoryManagement.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day02
{

using StringPair = std::pair<std::string, std::string>;

unsigned countWordsWithNRepeatingChars(const std::vector<std::string>& words, unsigned n)
{
    unsigned count = 0;
    std::for_each(words.cbegin(), words.cend(), [&count, n](const std::string& word)
                  {
                      std::unordered_map<char, unsigned> charCounts;
                      std::for_each(word.cbegin(), word.cend(), [&charCounts](char c)
                                    {
                                        ++charCounts[c];
                                    });

                      const bool matches = std::any_of(charCounts.cbegin(), charCounts.cend(), [n](const auto& element) noexcept
                                                 {
                                                     return element.second == n;
                                                 });

                      if (matches)
                      {
                          ++count;
                      }
                  });
    return count;
}

unsigned checksumTwoOrThreeOfAnyLetter(const std::vector<std::string>& words)
{
    const unsigned numWordsWithTwoRepeatingLetters = countWordsWithNRepeatingChars(words, 2);
    const unsigned numWordsWithThreeRepeatingLetters = countWordsWithNRepeatingChars(words, 3);

    return numWordsWithTwoRepeatingLetters * numWordsWithThreeRepeatingLetters;
}

StringPair findOneCharacterDiffStrings(const std::vector<std::string>& words)
{
    for (auto firstWordIter = words.cbegin(); firstWordIter != words.cend(); ++firstWordIter)
    {
        for (auto secondWordIter = firstWordIter + 1; secondWordIter != words.cend(); ++secondWordIter)
        {
            const std::string& firstWord = *firstWordIter;
            const std::string& secondWord = *secondWordIter;

            if (firstWord.length() != secondWord.length())
            {
                throw std::runtime_error("Words are of different length.");
            }

            unsigned diffCount = 0;
            for (size_t i = 0; i < firstWord.length(); ++i)
            {
                if (firstWord[i] != secondWord[i])
                {
                    ++diffCount;
                    if (diffCount > 1)
                    {
                        break;
                    }
                }
            }

            if (diffCount == 1)
            {
                return std::make_pair(*firstWordIter, *secondWordIter);
            }
        }
    }

    throw std::runtime_error("No two words with exactly one character difference.");
}

std::string commonLettersBetweenOneCharacterDiff(const std::vector<std::string>& words)
{
    if (words.size() < 2)
    {
        throw std::runtime_error("Input has fewer than two words.");
    }

    std::string firstWord;
    std::string secondWord;
    std::tie(firstWord, secondWord) = findOneCharacterDiffStrings(words);

    std::string commonLetters;
    for (size_t i = 0; i < firstWord.length(); ++i)
    {
        if (firstWord[i] == secondWord[i])
        {
            commonLetters += firstWord[i];
        }
    }

    return commonLetters;
}

}
}
}
