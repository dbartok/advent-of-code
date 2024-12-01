#pragma once

#include "DependencyScheduler.h"

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <cassert>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day07
{

DependencyScheduler::DependencyScheduler(DependencyGraph dependencyGraph, unsigned numWorkers, unsigned additionalDuration)
    : m_dependencyGraph{std::move(dependencyGraph)}
    , m_workers{numWorkers, Worker<NodeIDType>{}}
    , m_additionalDuration{additionalDuration}
    , m_nodeIDsReadyToStart{}
    , m_nodeIDsInProgress{}
    , m_numElapsedSteps{0}
{
    m_nodeIDsReadyToStart = m_dependencyGraph.getNodeIDsWithNoDependencies();
}

unsigned DependencyScheduler::getNumElapsedSteps() const noexcept
{
    return m_numElapsedSteps;
}

void DependencyScheduler::completeAllWork()
{
    while (!areAllWorkersIdle() || !m_dependencyGraph.isEmpty())
    {
        occupyIdleWorkers();

        executeWorkCycle();

        updateJobsReadyToStart();

        ++m_numElapsedSteps;
    }
}

bool DependencyScheduler::areAllWorkersIdle() const
{
    return std::all_of(m_workers.cbegin(), m_workers.cend(), [](const Worker<NodeIDType>& worker) noexcept {return worker.isIdle(); });
}

unsigned DependencyScheduler::getDurationForNodeID(NodeIDType nodeID) const noexcept
{
    return nodeID - FIRST_NODE_ID + 1 + m_additionalDuration;
}

void DependencyScheduler::updateJobsReadyToStart()
{
    m_nodeIDsReadyToStart = m_dependencyGraph.getNodeIDsWithNoDependencies();

    for (const auto& nodeID : m_nodeIDsInProgress)
    {
        m_nodeIDsReadyToStart.erase(nodeID);
    }
}

void DependencyScheduler::occupyIdleWorkers()
{
    for (auto& worker : m_workers)
    {
        if (m_nodeIDsReadyToStart.empty())
        {
            break;
        }

        if (worker.isIdle())
        {
            NodeIDType nextNodeID = *m_nodeIDsReadyToStart.cbegin();
            const unsigned nextDuration = getDurationForNodeID(nextNodeID);

            m_nodeIDsInProgress.insert(nextNodeID);

            worker.startWork(nextNodeID, nextDuration);
            m_nodeIDsReadyToStart.erase(m_nodeIDsReadyToStart.begin());
        }
    }
}

void DependencyScheduler::executeWorkCycle()
{
    for (auto& worker : m_workers)
    {
        worker.advanceCycle();

        if (worker.isFinished())
        {
            const NodeIDType finishedNodeID = worker.getNodeID();

            m_dependencyGraph.removeNode(finishedNodeID);
            m_nodeIDsInProgress.erase(finishedNodeID);

            worker.startIdling();
        }
    }
}

}
}
}
