#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day19
{

using Category = char;
using CategoryToRating = std::unordered_map<Category, int>;
using RatingRange = std::pair<int, int>;
using CategoryToRatingRange = std::unordered_map<Category, RatingRange>;

class Workflow;
using WorkflowNameToWorkflow = std::unordered_map<std::string, Workflow>;

struct WorkflowNode
{
    std::string name;
    CategoryToRatingRange range;

    WorkflowNode(std::string name, CategoryToRatingRange range)
        : name{std::move(name)}
        , range{std::move(range)}
    {

    }
};

class Rule
{
public:
    Rule(Category category, char condition, int threshold, std::string matchDestination);

    CategoryToRatingRange getMatchRange(CategoryToRatingRange baseRange) const;
    CategoryToRatingRange getNonMatchRange(CategoryToRatingRange baseRange) const;
    const std::string& getMatchDestination() const;

private:
    Category m_category;
    char m_condition;
    int m_threshold;
    std::string m_matchDestination;
};

class Workflow
{
public:
    Workflow(std::vector<Rule> rules);

    std::vector<WorkflowNode> getNextNodes(CategoryToRatingRange baseRange) const;

private:
    std::vector<Rule> m_rules;
};

class WorkflowAnalyzer
{
public:
    WorkflowAnalyzer(WorkflowNameToWorkflow workflowNameToWorkflow);

    void analyze();

    bool isAccepted(const CategoryToRating& part) const;
    int64_t getNumDistinctCombinationsAccepted() const;

private:
    WorkflowNameToWorkflow m_workflowNameToWorkflow;

    std::vector<CategoryToRatingRange> m_acceptedRanges;
};

}
}
}
