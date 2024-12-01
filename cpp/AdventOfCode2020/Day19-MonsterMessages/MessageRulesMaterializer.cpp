#include "MessageRulesMaterializer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day19
{

MessageRulesMaterializer::MessageRulesMaterializer(std::vector<std::string> messageRules)
{
    for (const auto& rule : messageRules)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, rule, boost::is_any_of(":"), boost::token_compress_on);

        const int ruleNumber = std::stoi(tokens.at(0));
        std::string matcherString = tokens.at(1).substr(1);
        m_ruleNumToMatcherString[ruleNumber] = std::move(matcherString);
    }
}

void MessageRulesMaterializer::materializeAll()
{
    for (const auto& ruleNumberAndMatcher : m_ruleNumToMatcherString)
    {
        materializeRuleWithCaching(ruleNumberAndMatcher.first);
    }
}

std::regex MessageRulesMaterializer::getRegexForRule(int ruleNumber) const
{
    return std::regex{m_ruleNumToMaterializedRule.at(ruleNumber)};
}

void MessageRulesMaterializer::materializeRuleWithCaching(int ruleNumber)
{
    if (m_ruleNumToMaterializedRule.find(ruleNumber) != m_ruleNumToMaterializedRule.cend())
    {
        return;
    }

    std::vector<std::string> tokens;
    boost::split(tokens, m_ruleNumToMatcherString.at(ruleNumber), boost::is_any_of(" "));

    replaceTokensWithMaterializedRules(tokens);

    std::string joinedTokens = "(" + boost::join(tokens, "") + ")";
    m_ruleNumToMaterializedRule[ruleNumber] = joinedTokens;
}

void MessageRulesMaterializer::replaceTokensWithMaterializedRules(std::vector<std::string>& tokens)
{
    for (auto& token : tokens)
    {
        if (token.front() == '\"')
        {
            token = token.substr(1, token.size() - 2);
        }
        else if (token != "|")
        {
            const int tokenRuleNumber = std::stoi(token);
            materializeRuleWithCaching(tokenRuleNumber);
            token = m_ruleNumToMaterializedRule.at(tokenRuleNumber);
        }
    }
}

}
}
}
