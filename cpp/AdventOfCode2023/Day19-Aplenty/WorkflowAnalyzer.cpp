#include "WorkflowAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const std::pair<int, int> DEFAULT_RANGE = {1, 4000};

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day19
{

Rule::Rule(Category category, char condition, int threshold, std::string matchDestination)
    : m_category{category}
    , m_condition{condition}
    , m_threshold{threshold}
    , m_matchDestination{std::move(matchDestination)}
{

}

CategoryToRatingRange Rule::getMatchRange(CategoryToRatingRange baseRange) const
{
    RatingRange& constrainedRange = baseRange.at(m_category);

    if (m_condition == '<')
    {
        constrainedRange.second = m_threshold - 1;
    }
    else
    {
        constrainedRange.first = m_threshold + 1;
    }

    return baseRange;
}

CategoryToRatingRange Rule::getNonMatchRange(CategoryToRatingRange baseRange) const
{
    RatingRange& constrainedRange = baseRange.at(m_category);

    if (m_condition == '<')
    {
        constrainedRange.first = m_threshold;
    }
    else
    {
        constrainedRange.second = m_threshold;
    }

    return baseRange;
}

const std::string& Rule::getMatchDestination() const
{
    return m_matchDestination;
}

Workflow::Workflow(std::vector<Rule> rules)
    : m_rules{std::move(rules)}
{

}

std::vector<WorkflowNode> Workflow::getNextNodes(CategoryToRatingRange baseRange) const
{
    std::vector<WorkflowNode> nextNodes;
    for (auto ruleIter = m_rules.cbegin(); ruleIter < m_rules.cend() - 1; ++ruleIter)
    {
        CategoryToRatingRange matchRange = ruleIter->getMatchRange(baseRange);
        nextNodes.emplace_back(ruleIter->getMatchDestination(), matchRange);

        baseRange = ruleIter->getNonMatchRange(baseRange);
    }

    // Last rule always matches
    nextNodes.emplace_back(m_rules.back().getMatchDestination(), baseRange);

    return nextNodes;
}

WorkflowAnalyzer::WorkflowAnalyzer(WorkflowNameToWorkflow workflowNameToWorkflow)
    : m_workflowNameToWorkflow{std::move(workflowNameToWorkflow)}
{

}

void WorkflowAnalyzer::analyze()
{
    WorkflowNode startNode{"in", {{'x', DEFAULT_RANGE}, {'m', DEFAULT_RANGE}, {'a', DEFAULT_RANGE}, {'s', DEFAULT_RANGE}}};
    std::queue<WorkflowNode> openNodes;
    openNodes.push(startNode);

    while (!openNodes.empty())
    {
        WorkflowNode currentNode = openNodes.front();
        openNodes.pop();

        const Workflow& currentWorkflow = m_workflowNameToWorkflow.at(currentNode.name);
        std::vector<WorkflowNode> nextNodes = currentWorkflow.getNextNodes(currentNode.range);

        for (auto& nextNode : nextNodes)
        {
            if (nextNode.name == "A")
            {
                m_acceptedRanges.push_back(nextNode.range);
            }
            else if (nextNode.name != "R")
            {
                openNodes.push(std::move(nextNode));
            }
        }
    }
}

bool WorkflowAnalyzer::isAccepted(const CategoryToRating& part) const
{
    return std::any_of(m_acceptedRanges.cbegin(), m_acceptedRanges.cend(), [&part](const auto& acceptedRange)
                       {
                           return std::all_of(part.cbegin(), part.cend(), [&acceptedRange](const auto& categoryAndRating)
                                              {
                                                  const auto& acceptedRangeForCategory = acceptedRange.at(categoryAndRating.first);
                                                  return categoryAndRating.second >= acceptedRangeForCategory.first && categoryAndRating.second <= acceptedRangeForCategory.second;
                                              });
                       });
}

int64_t WorkflowAnalyzer::getNumDistinctCombinationsAccepted() const
{
    return std::accumulate(m_acceptedRanges.cbegin(), m_acceptedRanges.cend(), 0ll, [](auto acc, const auto& acceptedRange)
                           {
                               return acc + std::accumulate(acceptedRange.cbegin(), acceptedRange.cend(), 1ll, [](auto acc, const auto& categoryAndRatingRange)
                                                            {
                                                                const auto& ratingRange = categoryAndRatingRange.second;
                                                                return acc * (ratingRange.second - ratingRange.first + 1);
                                                            });
                           });
}

}
}
}
