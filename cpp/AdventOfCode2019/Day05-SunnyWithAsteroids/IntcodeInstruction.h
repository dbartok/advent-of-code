#pragma once

#include "IntcodeProgramState.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
#include <string>
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day05
{

enum class IntcodeParameterMode
{
    IMMEDIATE,
    POSITION,
    RELATIVE,
};

class IntcodeParameter
{
public:
    IntcodeParameter(IntcodeNumberType value, IntcodeParameterMode parameterMode);

    IntcodeNumberType asRvalue(IntcodeProgamState& executionState) const;
    IntcodeNumberType& asLvalue(IntcodeProgamState& executionState) const;

private:
    IntcodeNumberType m_value;
    IntcodeParameterMode m_parameterMode;
};

class IntcodeInstruction
{
public:
    using SharedPtr = std::shared_ptr<IntcodeInstruction>;

    virtual void execute(IntcodeProgamState& state) const = 0;
    virtual void moveInstructionPointer(size_t& instructionPointer) const = 0;

    virtual ~IntcodeInstruction() = default;
};

class SingleParameterIntcodeInstruction : public IntcodeInstruction
{
public:
    SingleParameterIntcodeInstruction(IntcodeParameter param) noexcept;

    void moveInstructionPointer(size_t& instructionPointer) const override;

protected:
    IntcodeParameter m_param;
};

class HaltIntcodeInstruction : public IntcodeInstruction
{
public:
    void execute(IntcodeProgamState& state) const override;

    void moveInstructionPointer(size_t&) const override;
};

class InputIntcodeInstruction : public SingleParameterIntcodeInstruction
{
public:
    using SingleParameterIntcodeInstruction::SingleParameterIntcodeInstruction;

    void execute(IntcodeProgamState& state) const override;
};

class OutputIntcodeInstruction : public SingleParameterIntcodeInstruction
{
public:
    using SingleParameterIntcodeInstruction::SingleParameterIntcodeInstruction;

    void execute(IntcodeProgamState& state) const override;
};

class RelativeBaseOffsetInstruction : public SingleParameterIntcodeInstruction
{
public:
    using SingleParameterIntcodeInstruction::SingleParameterIntcodeInstruction;

    void execute(IntcodeProgamState& state) const override;
};

class DoubleParameterIntcodeInstruction : public IntcodeInstruction
{
public:
    DoubleParameterIntcodeInstruction(IntcodeParameter param1, IntcodeParameter param2) noexcept;

    void moveInstructionPointer(size_t& instructionPointer) const override;

protected:
    IntcodeParameter m_param1;
    IntcodeParameter m_param2;
};

class JumpIfTrueIntcodeInstruction : public DoubleParameterIntcodeInstruction
{
public:
    using DoubleParameterIntcodeInstruction::DoubleParameterIntcodeInstruction;

    void execute(IntcodeProgamState& state) const override;
};

class JumpIfFalseIntcodeInstruction : public DoubleParameterIntcodeInstruction
{
public:
    using DoubleParameterIntcodeInstruction::DoubleParameterIntcodeInstruction;

    void execute(IntcodeProgamState& state) const override;
};

class TripleParameterIntcodeInstruction : public IntcodeInstruction
{
public:
    TripleParameterIntcodeInstruction(IntcodeParameter param1, IntcodeParameter param2, IntcodeParameter param3) noexcept;

    void moveInstructionPointer(size_t& instructionPointer) const override;

protected:
    IntcodeParameter m_param1;
    IntcodeParameter m_param2;
    IntcodeParameter m_param3;
};

class AddIntcodeInstruction : public TripleParameterIntcodeInstruction
{
public:
    using TripleParameterIntcodeInstruction::TripleParameterIntcodeInstruction;

    void execute(IntcodeProgamState& state) const override;
};

class MultiplyIntcodeInstruction : public TripleParameterIntcodeInstruction
{
public:
    using TripleParameterIntcodeInstruction::TripleParameterIntcodeInstruction;

    void execute(IntcodeProgamState& state) const override;
};

class LessThanIntcodeInstruction : public TripleParameterIntcodeInstruction
{
public:
    using TripleParameterIntcodeInstruction::TripleParameterIntcodeInstruction;

    void execute(IntcodeProgamState& state) const override;
};

class EqualsIntcodeInstruction : public TripleParameterIntcodeInstruction
{
public:
    using TripleParameterIntcodeInstruction::TripleParameterIntcodeInstruction;

    void execute(IntcodeProgamState& state) const override;
};

}
}
}
