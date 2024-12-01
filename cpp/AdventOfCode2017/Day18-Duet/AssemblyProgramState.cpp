#include "AssemblyProgramState.h"

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

AssemblyProgramState::AssemblyProgramState() noexcept
    : m_executionState{ExecutionState::RUNNING}
    , m_instructionIndex{0}
    , m_registerNameToValue{}
    , m_lastPlayedFrequency{}
    , m_numTimesSent{0}
    , m_numTimesMultInvoked{0}
    , m_programID{}
    , m_messageQueueSharedPtr{nullptr}
{

}

ExecutionState& AssemblyProgramState::executionState() noexcept
{
    return m_executionState;
}

int& AssemblyProgramState::instructionIndex() noexcept
{
    return m_instructionIndex;
}

boost::optional<RegisterValueType>& AssemblyProgramState::lastPlayedFrequency() noexcept
{
    return m_lastPlayedFrequency;
}

unsigned& AssemblyProgramState::numTimesSent() noexcept
{
    return m_numTimesSent;
}

unsigned AssemblyProgramState::getNumTimesSent() const noexcept
{
    return m_numTimesSent;
}

unsigned& AssemblyProgramState::numTimesMultInvoked() noexcept
{
    return m_numTimesMultInvoked;
}

unsigned AssemblyProgramState::getNumTimesMultInvoked() const noexcept
{
    return m_numTimesMultInvoked;
}

ExecutionState AssemblyProgramState::getExecutionState() const noexcept
{
    return m_executionState;
}

const boost::optional<RegisterValueType>& AssemblyProgramState::getLastPlayedFrequency() const noexcept
{
    return m_lastPlayedFrequency;
}

void AssemblyProgramState::initMessageQueue(DuetMessageQueue::SharedPtr messageQueueSharedPtr) noexcept
{
    m_messageQueueSharedPtr = std::move(messageQueueSharedPtr);
}

DuetMessageQueue& AssemblyProgramState::messageQueue()
{
    if (!m_messageQueueSharedPtr)
    {
        throw std::runtime_error("Message queue wasn't initialized.");
    }

    return *m_messageQueueSharedPtr;
}

void AssemblyProgramState::initalizeProgramID(unsigned programID)
{
    m_programID = programID;
}


unsigned& AssemblyProgramState::programID()
{
    if (!m_programID)
    {
        throw std::runtime_error("Program ID wasn't initialized");
    }

    return m_programID.get();
}

unsigned AssemblyProgramState::getOpposingProgramID()
{
    return 1 - programID();
}

RegisterValueType AssemblyProgramState::getRegisterValue(const std::string& registerName) const
{
    const auto foundIter = m_registerNameToValue.find(registerName);
    if (foundIter == m_registerNameToValue.cend())
    {
        return 0;
    }

    return *foundIter->second;
}

std::shared_ptr<RegisterValueType> AssemblyProgramState::getRegisterValueSharedPtr(const std::string& registerName)
{
    auto foundIter = m_registerNameToValue.find(registerName);
    if (foundIter == m_registerNameToValue.end())
    {
        std::tie(foundIter, std::ignore) = m_registerNameToValue.insert(std::make_pair(registerName, std::make_shared<RegisterValueType>(0)));
    }

    return foundIter->second;
}

}
}
}
