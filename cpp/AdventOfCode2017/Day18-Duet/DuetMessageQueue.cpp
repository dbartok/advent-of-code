#include "DuetMessageQueue.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day18
{

DuetMessageQueue::DuetMessageQueue() noexcept
    : m_programIDToQueue(2) // Size constructor
{

}

void DuetMessageQueue::sendMessage(unsigned queueID, RegisterValueType value)
{
    validateQueueID(queueID);

    m_programIDToQueue[queueID].push_back(value);
}

boost::optional<RegisterValueType> DuetMessageQueue::tryReceiveMessage(unsigned queueID)
{
    validateQueueID(queueID);

    if (m_programIDToQueue[queueID].empty())
    {
        return boost::none;
    }

    auto retrievedValue = m_programIDToQueue[queueID].front();
    m_programIDToQueue[queueID].pop_front();

    return retrievedValue;
}

void DuetMessageQueue::validateQueueID(unsigned queueID)
{
    if (queueID > 1)
    {
        throw std::runtime_error("Only two queues are supported.");
    }
}

}
}
}
