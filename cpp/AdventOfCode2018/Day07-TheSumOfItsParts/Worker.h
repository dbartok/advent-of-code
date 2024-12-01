#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day07
{

template <typename WorkIDType>
class Worker
{
public:
    Worker() noexcept;

    bool isIdle() const noexcept;

    bool isFinished() const noexcept;
    const WorkIDType& getNodeID() const noexcept;

    void startWork(WorkIDType nodeID, unsigned duration) noexcept;
    void startIdling() noexcept;
    void advanceCycle() noexcept;

private:
    bool m_isIdle;
    WorkIDType m_workID;
    unsigned m_remainingDuration;
};

template<typename WorkIDType>
Worker<WorkIDType>::Worker() noexcept
    : m_isIdle(true)
    , m_workID{WorkIDType{}}
    , m_remainingDuration{0}
{

}

template<typename WorkIDType>
bool Worker<WorkIDType>::isIdle() const noexcept
{
    return m_isIdle;
}

template<typename WorkIDType>
bool Worker<WorkIDType>::isFinished() const noexcept
{
    return !isIdle() && m_remainingDuration == 0;
}

template<typename WorkIDType>
const WorkIDType& Worker<WorkIDType>::getNodeID() const noexcept
{
    return m_workID;
}

template<typename WorkIDType>
void Worker<WorkIDType>::startWork(WorkIDType nodeID, unsigned duration) noexcept
{
    m_isIdle = false;
    m_workID = std::move(nodeID);
    m_remainingDuration = duration;
}

template<typename WorkIDType>
void Worker<WorkIDType>::startIdling() noexcept
{
    m_isIdle = true;
}

template<typename WorkIDType>
void Worker<WorkIDType>::advanceCycle() noexcept
{
    if (!isIdle())
    {
        --m_remainingDuration;
    }
}

}
}
}
