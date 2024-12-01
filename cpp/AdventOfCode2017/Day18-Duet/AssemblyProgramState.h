#pragma once

#include "RegisterValueType.h"
#include "DuetMessageQueue.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <unordered_map>
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day18
{

enum class ExecutionState
{
    RUNNING,
    BLOCKED,
    UNABLE_TO_PROGRESS,
    TERMINATED
};

class AssemblyProgramState
{
public:
    AssemblyProgramState() noexcept;

    RegisterValueType getRegisterValue(const std::string& registerName) const;
    std::shared_ptr<RegisterValueType> getRegisterValueSharedPtr(const std::string& registerName);

    ExecutionState& executionState() noexcept;
    int& instructionIndex() noexcept;
    boost::optional<RegisterValueType>& lastPlayedFrequency() noexcept;
    unsigned& numTimesSent() noexcept;
    unsigned& numTimesMultInvoked() noexcept;

    ExecutionState getExecutionState() const noexcept;
    const boost::optional<RegisterValueType>& getLastPlayedFrequency() const noexcept;
    unsigned getNumTimesSent() const noexcept;
    unsigned getNumTimesMultInvoked() const noexcept;

    void initalizeProgramID(unsigned programID);
    unsigned& programID();

    void initMessageQueue(DuetMessageQueue::SharedPtr messageQueueSharedPtr) noexcept;
    DuetMessageQueue& messageQueue();

    unsigned getOpposingProgramID();

private:
    using RegisterNameToValueMap = std::unordered_map<std::string, std::shared_ptr<RegisterValueType>>;

    ExecutionState m_executionState;
    int m_instructionIndex;
    RegisterNameToValueMap m_registerNameToValue;
    boost::optional<RegisterValueType> m_lastPlayedFrequency;
    unsigned m_numTimesSent;
    unsigned m_numTimesMultInvoked;

    boost::optional<unsigned> m_programID;
    DuetMessageQueue::SharedPtr m_messageQueueSharedPtr;
};

}
}
}
