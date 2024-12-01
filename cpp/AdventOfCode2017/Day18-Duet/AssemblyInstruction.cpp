#include "AssemblyInstruction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cctype>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day18
{

RegisterOrNumberArg::RegisterOrNumberArg(std::string argString)
    : m_registerNameOrRawValue{std::move(argString)}
{
    if (m_registerNameOrRawValue.empty())
    {
        throw std::runtime_error("Empty argument.");
    }
}

bool RegisterOrNumberArg::isRegisterBound() const
{
    if (std::islower(m_registerNameOrRawValue.front()) != 0)
    {
        return true;
    }

    return false;
}

const std::string& RegisterOrNumberArg::asRegisterName() const
{
    if (isRegisterBound())
    {
        return m_registerNameOrRawValue;
    }

    throw std::runtime_error("Cannot evaluate argument as register name.");
}

RegisterValueType RegisterOrNumberArg::asValue(const AssemblyProgramState& state) const
{
    if (isRegisterBound())
    {
        return state.getRegisterValue(m_registerNameOrRawValue);
    }

    return std::stoi(m_registerNameOrRawValue);
}

std::shared_ptr<RegisterValueType> RegisterOrNumberArg::asRegisterValueSharedPtr(AssemblyProgramState& state) const
{
    if (isRegisterBound())
    {
        return state.getRegisterValueSharedPtr(m_registerNameOrRawValue);
    }

    throw std::runtime_error("Cannot evaluate argument as register value.");
}

bool AssemblyInstruction::increasesInstructionIndex() const noexcept
{
    return true;
}

SingleArgInstruction::SingleArgInstruction(RegisterOrNumberArg arg) noexcept
    : m_arg{std::move(arg)}
{

}

DoubleArgInstruction::DoubleArgInstruction(RegisterOrNumberArg arg1, RegisterOrNumberArg arg2) noexcept
    : m_arg1{std::move(arg1)}
    , m_arg2{std::move(arg2)}
{

}

void SoundInstruction::execute(AssemblyProgramState& state) const
{
    state.lastPlayedFrequency() = m_arg.asValue(state);
}

void RecoverInstruction::execute(AssemblyProgramState& state) const
{
    if (m_arg.asValue(state) != 0)
    {
        state.executionState() = ExecutionState::TERMINATED;
    }
}

void SendInstruction::execute(AssemblyProgramState& state) const
{
    state.messageQueue().sendMessage(state.getOpposingProgramID(), m_arg.asValue(state));
    ++state.numTimesSent();
}

void ReceiveInstruction::execute(AssemblyProgramState& state) const
{
    boost::optional<RegisterValueType> receivedValue = state.messageQueue().tryReceiveMessage(state.programID());
    if (!receivedValue)
    {
        state.executionState() = ExecutionState::BLOCKED;
    }
    else
    {
        *m_arg.asRegisterValueSharedPtr(state) = receivedValue.get();
    }

}

void SetInstruction::execute(AssemblyProgramState& state) const
{
    *m_arg1.asRegisterValueSharedPtr(state) = m_arg2.asValue(state);
}

void AddInstruction::execute(AssemblyProgramState& state) const
{
    *m_arg1.asRegisterValueSharedPtr(state) += m_arg2.asValue(state);
}

void MultiplyInstruction::execute(AssemblyProgramState& state) const
{
    *m_arg1.asRegisterValueSharedPtr(state) *= m_arg2.asValue(state);
    ++state.numTimesMultInvoked();
}

void ModuloInstruction::execute(AssemblyProgramState& state) const
{
    auto& arg1 = *m_arg1.asRegisterValueSharedPtr(state);
    arg1 = arg1 % m_arg2.asValue(state);
}

void JumpGreaterThanZeroInstruction::execute(AssemblyProgramState& state) const
{
    if (m_arg1.asValue(state) > 0)
    {
        state.instructionIndex() += m_arg2.asValue(state);
    }
    else
    {
        ++state.instructionIndex();
    }
}

bool JumpGreaterThanZeroInstruction::increasesInstructionIndex() const noexcept
{
    return false;
}

void SubtractInstruction::execute(AssemblyProgramState& state) const
{
    *m_arg1.asRegisterValueSharedPtr(state) -= m_arg2.asValue(state);
}

void JumpNotZeroInstruction::execute(AssemblyProgramState& state) const
{
    if (m_arg1.asValue(state) != 0)
    {
        state.instructionIndex() += m_arg2.asValue(state);
    }
    else
    {
        ++state.instructionIndex();
    }
}

bool JumpNotZeroInstruction::increasesInstructionIndex() const noexcept
{
    return false;
}

}
}
}
