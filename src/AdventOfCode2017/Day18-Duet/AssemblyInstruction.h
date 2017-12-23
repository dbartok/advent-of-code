#pragma once

#include "AssemblyProgramState.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <memory>
#include <string>
END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

class RegisterOrNumberArg
{
public:
    RegisterOrNumberArg(std::string argString);
    bool isRegisterBound() const;
    const std::string& asRegisterName() const;
    RegisterValueType asValue(const AssemblyProgramState& state) const;
    std::shared_ptr<RegisterValueType> asRegisterValueSharedPtr(AssemblyProgramState& state) const;
private:
    std::string m_registerNameOrRawValue;
};

class AssemblyInstruction
{
public:
    using SharedPtr = std::shared_ptr<AssemblyInstruction>;

    AssemblyInstruction() = default;

    AssemblyInstruction(const AssemblyInstruction&) = default;
    AssemblyInstruction(AssemblyInstruction&&) = default;
    AssemblyInstruction& operator=(const AssemblyInstruction&) = default;
    AssemblyInstruction& operator=(AssemblyInstruction&&) = default;
    virtual ~AssemblyInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const = 0;
    virtual bool increasesInstructionIndex() const noexcept;
};

class SingleArgInstruction : public AssemblyInstruction
{
public:
    SingleArgInstruction(RegisterOrNumberArg arg) noexcept;

    SingleArgInstruction(const SingleArgInstruction&) = default;
    SingleArgInstruction(SingleArgInstruction&&) = default;
    SingleArgInstruction& operator=(const SingleArgInstruction&) = default;
    SingleArgInstruction& operator=(SingleArgInstruction&&) = default;
    virtual ~SingleArgInstruction() = default;
protected:
    RegisterOrNumberArg m_arg;
};

class DoubleArgInstruction : public AssemblyInstruction
{
public:
    DoubleArgInstruction(RegisterOrNumberArg arg1, RegisterOrNumberArg arg2) noexcept;

    DoubleArgInstruction(const DoubleArgInstruction&) = default;
    DoubleArgInstruction(DoubleArgInstruction&&) = default;
    DoubleArgInstruction& operator=(const DoubleArgInstruction&) = default;
    DoubleArgInstruction& operator=(DoubleArgInstruction&&) = default;
    virtual ~DoubleArgInstruction() = default;
protected:
    RegisterOrNumberArg m_arg1;
    RegisterOrNumberArg m_arg2;
};

class SoundInstruction : public SingleArgInstruction
{
public:
    using SingleArgInstruction::SingleArgInstruction;

    SoundInstruction(const SoundInstruction&) = default;
    SoundInstruction(SoundInstruction&&) = default;
    SoundInstruction& operator=(const SoundInstruction&) = default;
    SoundInstruction& operator=(SoundInstruction&&) = default;
    virtual ~SoundInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
};

class RecoverInstruction : public SingleArgInstruction
{
public:
    using SingleArgInstruction::SingleArgInstruction;

    RecoverInstruction(const RecoverInstruction&) = default;
    RecoverInstruction(RecoverInstruction&&) = default;
    RecoverInstruction& operator=(const RecoverInstruction&) = default;
    RecoverInstruction& operator=(RecoverInstruction&&) = default;
    virtual ~RecoverInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
};

class SendInstruction : public SingleArgInstruction
{
public:
    using SingleArgInstruction::SingleArgInstruction;

    SendInstruction(const SendInstruction&) = default;
    SendInstruction(SendInstruction&&) = default;
    SendInstruction& operator=(const SendInstruction&) = default;
    SendInstruction& operator=(SendInstruction&&) = default;
    virtual ~SendInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
};

class ReceiveInstruction : public SingleArgInstruction
{
public:
    using SingleArgInstruction::SingleArgInstruction;

    ReceiveInstruction(const ReceiveInstruction&) = default;
    ReceiveInstruction(ReceiveInstruction&&) = default;
    ReceiveInstruction& operator=(const ReceiveInstruction&) = default;
    ReceiveInstruction& operator=(ReceiveInstruction&&) = default;
    virtual ~ReceiveInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
};

class SetInstruction : public DoubleArgInstruction
{
public:
    using DoubleArgInstruction::DoubleArgInstruction;

    SetInstruction(const SetInstruction&) = default;
    SetInstruction(SetInstruction&&) = default;
    SetInstruction& operator=(const SetInstruction&) = default;
    SetInstruction& operator=(SetInstruction&&) = default;
    virtual ~SetInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
};

class AddInstruction : public DoubleArgInstruction
{
public:
    using DoubleArgInstruction::DoubleArgInstruction;

    AddInstruction(const AddInstruction&) = default;
    AddInstruction(AddInstruction&&) = default;
    AddInstruction& operator=(const AddInstruction&) = default;
    AddInstruction& operator=(AddInstruction&&) = default;
    virtual ~AddInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
};

class MultiplyInstruction : public DoubleArgInstruction
{
public:
    using DoubleArgInstruction::DoubleArgInstruction;

    MultiplyInstruction(const MultiplyInstruction&) = default;
    MultiplyInstruction(MultiplyInstruction&&) = default;
    MultiplyInstruction& operator=(const MultiplyInstruction&) = default;
    MultiplyInstruction& operator=(MultiplyInstruction&&) = default;
    virtual ~MultiplyInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
};

class ModuloInstruction : public DoubleArgInstruction
{
public:
    using DoubleArgInstruction::DoubleArgInstruction;

    ModuloInstruction(const ModuloInstruction&) = default;
    ModuloInstruction(ModuloInstruction&&) = default;
    ModuloInstruction& operator=(const ModuloInstruction&) = default;
    ModuloInstruction& operator=(ModuloInstruction&&) = default;
    virtual ~ModuloInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
};

class JumpGreaterThanZeroInstruction : public DoubleArgInstruction
{
public:
    using DoubleArgInstruction::DoubleArgInstruction;

    JumpGreaterThanZeroInstruction(const JumpGreaterThanZeroInstruction&) = default;
    JumpGreaterThanZeroInstruction(JumpGreaterThanZeroInstruction&&) = default;
    JumpGreaterThanZeroInstruction& operator=(const JumpGreaterThanZeroInstruction&) = default;
    JumpGreaterThanZeroInstruction& operator=(JumpGreaterThanZeroInstruction&&) = default;
    virtual ~JumpGreaterThanZeroInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
    virtual bool increasesInstructionIndex() const noexcept override;
};

class SubtractInstruction : public DoubleArgInstruction
{
public:
    using DoubleArgInstruction::DoubleArgInstruction;

    SubtractInstruction(const SubtractInstruction&) = default;
    SubtractInstruction(SubtractInstruction&&) = default;
    SubtractInstruction& operator=(const SubtractInstruction&) = default;
    SubtractInstruction& operator=(SubtractInstruction&&) = default;
    virtual ~SubtractInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
};

class JumpNotZeroInstruction : public DoubleArgInstruction
{
public:
    using DoubleArgInstruction::DoubleArgInstruction;

    JumpNotZeroInstruction(const JumpNotZeroInstruction&) = default;
    JumpNotZeroInstruction(JumpNotZeroInstruction&&) = default;
    JumpNotZeroInstruction& operator=(const JumpNotZeroInstruction&) = default;
    JumpNotZeroInstruction& operator=(JumpNotZeroInstruction&&) = default;
    virtual ~JumpNotZeroInstruction() = default;

    virtual void execute(AssemblyProgramState& state) const override;
    virtual bool increasesInstructionIndex() const noexcept override;
};

}
