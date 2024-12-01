#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
#include <unordered_map>
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day19
{

class MessageRulesMaterializer
{
public:
    MessageRulesMaterializer(std::vector<std::string> messageRules);

    void materializeAll();

    std::regex getRegexForRule(int ruleNumber) const;

private:
    std::unordered_map<int, std::string> m_ruleNumToMatcherString;
    std::unordered_map<int, std::string> m_ruleNumToMaterializedRule;

    void materializeRuleWithCaching(int ruleNumber);
    void replaceTokensWithMaterializedRules(std::vector<std::string>& tokens);
};

}
}
}
