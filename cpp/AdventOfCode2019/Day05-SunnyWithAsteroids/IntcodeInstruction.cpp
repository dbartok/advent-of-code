#include "IntcodeInstruction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day05
{

IntcodeParameter::IntcodeParameter(IntcodeNumberType value, IntcodeParameterMode parameterMode)
    : m_value{value}
    , m_parameterMode{parameterMode}
{

}

IntcodeNumberType IntcodeParameter::asRvalue(IntcodeProgamState& executionState) const
{
    if (m_parameterMode == IntcodeParameterMode::IMMEDIATE)
    {
        return m_value;
    }
    else if (m_parameterMode == IntcodeParameterMode::POSITION)
    {
        return executionState.program.at(m_value);
    }
    else if (m_parameterMode == IntcodeParameterMode::RELATIVE)
    {
        return executionState.program.at(m_value + executionState.relativeBase);
    }

    throw std::runtime_error("Invalid parameter mode for Rvalue resolution: " + std::to_string(static_cast<int>(m_parameterMode)));
}

IntcodeNumberType& IntcodeParameter::asLvalue(IntcodeProgamState& executionState) const
{
    if (m_parameterMode == IntcodeParameterMode::POSITION)
    {
        return executionState.program.at(m_value);
    }
    else if (m_parameterMode == IntcodeParameterMode::RELATIVE)
    {
        return executionState.program.at(m_value + executionState.relativeBase);
    }

    throw std::runtime_error("Invalid parameter mode for Lvalue resolution: " + std::to_string(static_cast<int>(m_parameterMode)));
}

SingleParameterIntcodeInstruction::SingleParameterIntcodeInstruction(IntcodeParameter param) noexcept
    : m_param{std::move(param)}
{

}

void SingleParameterIntcodeInstruction::moveInstructionPointer(size_t& instructionPointer) const
{
    instructionPointer += 2;
}

void HaltIntcodeInstruction::execute(IntcodeProgamState& state) const
{
    state.executionState = IntcodeProgramExecutionState::TERMINATED;
}

void HaltIntcodeInstruction::moveInstructionPointer(size_t&) const
{

}

void InputIntcodeInstruction::execute(IntcodeProgamState& state) const
{
    if (state.inputs.empty())
    {
        state.executionState = IntcodeProgramExecutionState::WAITING_FOR_INPUT;
        state.instructionPointer -= 2;
    }
    else
    {
        m_param.asLvalue(state) = state.inputs.front();
        state.inputs.erase(state.inputs.begin());
    }
}

void OutputIntcodeInstruction::execute(IntcodeProgamState& state) const
{
    state.outputs.push_back(m_param.asRvalue(state));
}

void RelativeBaseOffsetInstruction::execute(IntcodeProgamState& state) const
{
    state.relativeBase += m_param.asRvalue(state);
}

DoubleParameterIntcodeInstruction::DoubleParameterIntcodeInstruction(IntcodeParameter param1, IntcodeParameter param2) noexcept
    : m_param1{std::move(param1)}
    , m_param2{std::move(param2)}
{

}

void DoubleParameterIntcodeInstruction::moveInstructionPointer(size_t& instructionPointer) const
{
    instructionPointer += 3;
}

void JumpIfTrueIntcodeInstruction::execute(IntcodeProgamState& state) const
{
    if (m_param1.asRvalue(state) != 0)
    {
        state.instructionPointer = m_param2.asRvalue(state) - 3;
    }
}

void JumpIfFalseIntcodeInstruction::execute(IntcodeProgamState& state) const
{
    if (m_param1.asRvalue(state) == 0)
    {
        state.instructionPointer = m_param2.asRvalue(state) - 3;
    }
}

TripleParameterIntcodeInstruction::TripleParameterIntcodeInstruction(IntcodeParameter param1, IntcodeParameter param2, IntcodeParameter param3) noexcept
    : m_param1{std::move(param1)}
    , m_param2{std::move(param2)}
    , m_param3{std::move(param3)}
{

}

void TripleParameterIntcodeInstruction::moveInstructionPointer(size_t& instructionPointer) const
{
    instructionPointer += 4;
}

void AddIntcodeInstruction::execute(IntcodeProgamState& state) const
{
    m_param3.asLvalue(state) = m_param1.asRvalue(state) + m_param2.asRvalue(state);
}

void MultiplyIntcodeInstruction::execute(IntcodeProgamState& state) const
{
    m_param3.asLvalue(state) = m_param1.asRvalue(state) * m_param2.asRvalue(state);
}

void LessThanIntcodeInstruction::execute(IntcodeProgamState& state) const
{
    m_param3.asLvalue(state) = (m_param1.asRvalue(state) < m_param2.asRvalue(state));
}

void EqualsIntcodeInstruction::execute(IntcodeProgamState& state) const
{
    m_param3.asLvalue(state) = (m_param1.asRvalue(state) == m_param2.asRvalue(state));
}

}
}
}
