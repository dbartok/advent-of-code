#include "Day19-Aplenty.h"

#include "WorkflowAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day19
{

Rule createRule(const std::string& ruleString)
{
    std::vector<std::string> ruleStringTokens;
    boost::split(ruleStringTokens, ruleString, boost::is_any_of("<>:"));

    if (ruleStringTokens.size() == 1)
    {
        return Rule{'\0', '\0', 0, ruleString};
    }
    else
    {
        return Rule{ruleString.at(0), ruleString.at(1), std::stoi(ruleStringTokens.at(1)), ruleStringTokens.at(2)};
    }
}

Workflow createWorkflow(const std::string& workflowString)
{
    std::vector<std::string> workflowStringTokens;
    boost::split(workflowStringTokens, workflowString, boost::is_any_of(","));

    std::vector<Rule> rules;

    for (const auto& ruleString : workflowStringTokens)
    {
        Rule rule = createRule(ruleString);
        rules.push_back(std::move(rule));
    }

    return rules;
}

CategoryToRating createPart(const std::string& partLine)
{
    const std::string partString = partLine.substr(1, partLine.size() - 2);
    std::vector<std::string> partLineTokens;
    boost::split(partLineTokens, partString, boost::is_any_of(","));

    CategoryToRating categoryToRating;

    for (const auto& categoryAndRatingString : partLineTokens)
    {
        std::vector<std::string> categoryAndRatingStringTokens;
        boost::split(categoryAndRatingStringTokens, categoryAndRatingString, boost::is_any_of("="));

        categoryToRating.emplace(categoryAndRatingStringTokens.at(0).front(), std::stoi(categoryAndRatingStringTokens.at(1)));
    }

    return categoryToRating;
}

WorkflowAnalyzer createWorkflowAnalyzer(const std::vector<std::string>& systemLines)
{
    WorkflowNameToWorkflow workflowNameToWorkflow;

    for (auto workflowLineIter = systemLines.cbegin(); !workflowLineIter->empty(); ++workflowLineIter)
    {
        std::vector<std::string> workflowLineTokens;
        boost::split(workflowLineTokens, *workflowLineIter, boost::is_any_of("{}"));
        Workflow workflow = createWorkflow(workflowLineTokens.at(1));
        workflowNameToWorkflow.emplace(std::move(workflowLineTokens.at(0)), std::move(workflow));
    }

    return {std::move(workflowNameToWorkflow)};
}

std::vector<CategoryToRating> createParts(const std::vector<std::string>& systemLines)
{
    std::vector<CategoryToRating> parts;

    for (auto partLineIter = systemLines.crbegin(); !partLineIter->empty(); ++partLineIter)
    {
        CategoryToRating part = createPart(*partLineIter);
        parts.push_back(std::move(part));
    }

    return parts;
}

int sumOfRatingNumbersOfAllAcceptedParts(const std::vector<std::string>& systemLines)
{
    WorkflowAnalyzer workflowAnalyzer = createWorkflowAnalyzer(systemLines);
    std::vector<CategoryToRating> parts = createParts(systemLines);

    workflowAnalyzer.analyze();

    return std::accumulate(parts.cbegin(), parts.cend(), 0, [&workflowAnalyzer](auto acc, const auto& part)
                           {
                               if (workflowAnalyzer.isAccepted(part))
                               {
                                   acc += std::accumulate(part.cbegin(), part.cend(), 0, [](auto acc, const auto& categoryAndRating)
                                                          {
                                                              return acc + categoryAndRating.second;
                                                          });
                               }
                               return acc;
                           });
}

int64_t numDistinctCombinationsAccepted(const std::vector<std::string>& systemLines)
{
    WorkflowAnalyzer workflowAnalyzer = createWorkflowAnalyzer(systemLines);
    std::vector<CategoryToRating> parts = createParts(systemLines);

    workflowAnalyzer.analyze();

    return workflowAnalyzer.getNumDistinctCombinationsAccepted();
}

}
}
}