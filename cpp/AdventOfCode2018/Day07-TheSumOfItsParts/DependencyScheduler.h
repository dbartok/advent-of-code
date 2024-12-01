#pragma once

#include "DependencyGraph.h"
#include "Worker.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day07
{

class DependencyScheduler
{
public:
    DependencyScheduler(DependencyGraph dependencyGraph, unsigned numWorkers, unsigned additionalDuration);

    unsigned getNumElapsedSteps() const noexcept;

    void completeAllWork();

private:
    const unsigned FIRST_NODE_ID = 'A';

    DependencyGraph m_dependencyGraph;
    std::vector<Worker<NodeIDType>> m_workers;
    unsigned m_additionalDuration;

    std::set<NodeIDType> m_nodeIDsReadyToStart;
    std::unordered_set<NodeIDType> m_nodeIDsInProgress;
    unsigned m_numElapsedSteps;

    bool areAllWorkersIdle() const;
    unsigned getDurationForNodeID(NodeIDType nodeID) const noexcept;

    void updateJobsReadyToStart();
    void occupyIdleWorkers();
    void executeWorkCycle();
};

}
}
}
