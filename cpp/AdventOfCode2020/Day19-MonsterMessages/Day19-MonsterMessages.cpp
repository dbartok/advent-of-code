#include "Day19-MonsterMessages.h"

#include "MessageRulesMaterializer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int LEFT_INFINITE_RULE_NUMBER = 42;
const int RIGHT_INFINITE_RULE_NUMBER = 31;

}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day19
{

size_t getChunkSize(const std::vector<std::string>& messageLines)
{
    auto shortestMessageIter = std::min_element(messageLines.cbegin(), messageLines.cend(), [](const auto& lhs, const auto& rhs)
                                                {
                                                    return lhs.size() < rhs.size();
                                                });

    // Each message contains at least 3 chunks (the left infinite rule
    // occurring twice followed by the right infinite rule occurring once)
    return shortestMessageIter->size() / 3;

}

std::vector<std::string> splitStringIntoChunks(const std::string& str, size_t chunkSize)
{
    std::vector<std::string> chunks;
    for (size_t i = 0; i < str.size(); i += chunkSize)
    {
        chunks.push_back(str.substr(i, chunkSize));
    }
    return chunks;
}

template <typename Iterator>
size_t getNumMaximalConsecutiveMatchesFromStart(Iterator begin, Iterator end, const std::regex& regex)
{
    auto iter = begin;
    for (; iter != end; ++iter)
    {
        if (!std::regex_match(*iter, regex))
        {
            break;
        }
    }

    return std::distance(begin, iter);
}

bool isInfiniteMatching(const std::vector<std::string>& messageChunks, const std::regex& leftInfiniteRegex, const std::regex& rightInfiniteRegex)
{
    const size_t numMaximalLeftMatches = getNumMaximalConsecutiveMatchesFromStart(messageChunks.cbegin(), messageChunks.cend(), leftInfiniteRegex);
    const size_t numMaximalRightMatches = getNumMaximalConsecutiveMatchesFromStart(messageChunks.crbegin(), messageChunks.crend(), rightInfiniteRegex);

    const size_t numMessagesThatCannotBeMatchedFromLeft = messageChunks.size() - numMaximalLeftMatches;

    // The right infinite rule needs to occur at least once
    const size_t numRequiredRightMatches = std::max(static_cast<size_t>(1u), numMessagesThatCannotBeMatchedFromLeft);

    if (numRequiredRightMatches > numMaximalRightMatches)
    {
        return false;
    }

    // The left infinite rule occurs once on its own, then each time the right
    // infinite rule occurs, the left infinite rule has to occur once with it
    const size_t numRequiredLeftMatches = 1 + numRequiredRightMatches;

    if (numRequiredLeftMatches + numRequiredRightMatches > messageChunks.size())
    {
        return false;
    }

    return true;
}

int numMessagesMatchingRuleZero(const std::vector<std::string>& ruleAndMessageLines)
{
    std::vector<std::vector<std::string>> sections;
    boost::split(sections, ruleAndMessageLines, [](const auto& line) {return line.empty(); });

    MessageRulesMaterializer materializer{sections.at(0)};
    materializer.materializeAll();

    const std::regex messageRegex = materializer.getRegexForRule(0);

    const std::vector<std::string>& messages = sections.at(1);

    return std::count_if(messages.cbegin(), messages.cend(), [&messageRegex](const auto& message)
                         {
                             return std::regex_match(message, messageRegex);
                         });
}

int numMessagesMatchingRuleZeroWithInfiniteRules(const std::vector<std::string>& ruleAndMessageLines)
{
    std::vector<std::vector<std::string>> sections;
    boost::split(sections, ruleAndMessageLines, [](const auto& line) {return line.empty(); });

    MessageRulesMaterializer materializer{sections.at(0)};
    materializer.materializeAll();

    const std::regex leftInfiniteRegex = materializer.getRegexForRule(LEFT_INFINITE_RULE_NUMBER);
    const std::regex rightInfiniteRegex = materializer.getRegexForRule(RIGHT_INFINITE_RULE_NUMBER);

    const std::vector<std::string>& messages = sections.at(1);
    const size_t chunkSize = getChunkSize(messages);

    return std::count_if(messages.cbegin(), messages.cend(), [&leftInfiniteRegex, &rightInfiniteRegex, chunkSize](const auto& message)
                         {
                             std::vector<std::string> chunks = splitStringIntoChunks(message, chunkSize);
                             return isInfiniteMatching(std::move(chunks), leftInfiniteRegex, rightInfiniteRegex);
                         });
}

}
}
}
