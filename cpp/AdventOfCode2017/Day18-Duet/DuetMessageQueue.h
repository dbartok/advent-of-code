#pragma once

#include "RegisterValueType.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <vector>
#include <deque>
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day18
{

class DuetMessageQueue
{
public:
    using SharedPtr = std::shared_ptr<DuetMessageQueue>;

    DuetMessageQueue() noexcept;
    void sendMessage(unsigned queueID, RegisterValueType value);
    boost::optional<RegisterValueType> tryReceiveMessage(unsigned queueID);

private:
    std::vector<std::deque<RegisterValueType>> m_programIDToQueue;

    void validateQueueID(unsigned queueID);
};

}
}
}
