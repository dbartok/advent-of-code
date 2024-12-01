#include "SubmarineReactorRebooter.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int INITIALIZATION_AREA_SIZE = 50;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day22
{

bool RebootStep::isInitializationStep() const
{
    return std::all_of(intervalDimensions.cbegin(), intervalDimensions.cend(), [](const auto& intervalDimension)
                        {
                            return intervalDimension.first >= -INITIALIZATION_AREA_SIZE && intervalDimension.first <= INITIALIZATION_AREA_SIZE &&
                                intervalDimension.second >= -INITIALIZATION_AREA_SIZE && intervalDimension.second <= INITIALIZATION_AREA_SIZE;
                        });
}

void Node::insertRebootStep(const RebootStep& rebootStep)
{
    assert(!rebootStep.intervalDimensions.empty());

    const Interval& currentInterval = rebootStep.intervalDimensions.front();

    splitAt(currentInterval.first);
    splitAt(currentInterval.second + 1);

    std::vector<Node*> nodesInRange = getNodesInRange(currentInterval);

    std::vector<Interval> reducedIntervalDimensions = {rebootStep.intervalDimensions.cbegin() + 1, rebootStep.intervalDimensions.cend()};
    for (auto nodeToModify : nodesInRange)
    {
        if (reducedIntervalDimensions.empty())
        {
            nodeToModify->m_state = rebootStep.state;
        }
        else
        {
            assert(!nodeToModify->m_state.has_value());
            nodeToModify->insertRebootStep(RebootStep{rebootStep.state, reducedIntervalDimensions});
        }
    }
}

uint64_t Node::getNumCubesOn() const
{
    assert(!m_state.has_value());
    return getNumCubesOnRecursive(1);
}

void Node::splitAt(int threshold)
{
    auto upperBoundIter = m_intervals.upper_bound(threshold);
    Node newNode;

    // This isn't the first node or last node
    if (upperBoundIter != m_intervals.cbegin())
    {
        const auto prevNodeIter = std::prev(upperBoundIter);
        newNode = prevNodeIter->second;
    }

    m_intervals.emplace(threshold, std::move(newNode));
}

std::vector<Node*> Node::getNodesInRange(const Interval& interval)
{
    std::vector<Node*> nodesInRange;

    const auto beginIter = m_intervals.find(interval.first);
    const auto endIter = m_intervals.find(interval.second + 1);

    assert(beginIter != m_intervals.cend() && endIter != m_intervals.cend());

    for (auto nodeIter = beginIter; nodeIter != endIter; ++nodeIter)
    {
        nodesInRange.push_back(&(nodeIter->second));
    }

    return nodesInRange;
}

uint64_t Node::getNumCubesOnRecursive(uint64_t multiplyingFactor) const
{
    if (m_intervals.empty())
    {
        return 0;
    }
    assert(m_intervals.size() != 1);

    uint64_t totalNumCubesOn = 0;

    for (auto nodeIter = m_intervals.cbegin(); std::next(nodeIter) != m_intervals.cend(); ++nodeIter)
    {
        const int intervalLength = std::next(nodeIter)->first - nodeIter->first;
        const Node& childNode = nodeIter->second;
        if (childNode.m_state.has_value())
        {
            assert(childNode.m_intervals.empty());
            assert(intervalLength > 0);
            totalNumCubesOn += multiplyingFactor * intervalLength * childNode.m_state.value();
        }
        else
        {
            const uint64_t newMultiplyingFactor = multiplyingFactor * intervalLength;
            totalNumCubesOn += childNode.getNumCubesOnRecursive(newMultiplyingFactor);
        }
    }

    return totalNumCubesOn;
}

SubmarineReactorRebooter::SubmarineReactorRebooter(std::vector<RebootStep> rebootSteps)
    : m_rebootSteps{std::move(rebootSteps)}
    , m_rootNode{}
{

}

void SubmarineReactorRebooter::executeRebootInitializationProcedure()
{
    for (const auto& rebootStep : m_rebootSteps)
    {
        if (rebootStep.isInitializationStep())
        {
            executeRebootStep(rebootStep);
        }
    }
}

void SubmarineReactorRebooter::executeRebootFullRebootProcedure()
{
    for (const auto& rebootStep : m_rebootSteps)
    {
        m_rootNode.insertRebootStep(rebootStep);
    }
}

uint64_t SubmarineReactorRebooter::getNumCubesOn() const
{
    return m_rootNode.getNumCubesOn();
}

void SubmarineReactorRebooter::executeRebootStep(const RebootStep& rebootStep)
{
    m_rootNode.insertRebootStep(rebootStep);
}

}
}
}
