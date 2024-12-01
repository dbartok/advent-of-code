#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <vector>
#include <string>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day14
{

enum class InstructionType
{
    MASK,
    MEM,
};

struct Instruction
{
    Instruction(InstructionType type, std::string arg, uint64_t addr);
    Instruction(InstructionType type, std::string arg);

    InstructionType type;
    std::string arg;
    boost::optional<uint64_t> addr;
};

class BitmaskProgramExecutor
{
public:
    BitmaskProgramExecutor(std::vector<Instruction> instructions);

    void execute();

    uint64_t getSumOfValuesInMemory() const;

protected:
    std::vector<Instruction> m_instructions;

    uint64_t m_andBitmask = ~0ull;
    uint64_t m_orBitmask = 0ull;
    std::unordered_map<uint64_t, uint64_t> m_memoryLocationToValue;

    virtual void executeMemInstruction(const Instruction& instruction);
    virtual void executeMaskInstruction(const Instruction& instruction);

private:
    void executeInstruction(const Instruction& instruction);
};

class BitmaskDecoderProgramExecutor : public BitmaskProgramExecutor
{
public:
    using BitmaskProgramExecutor::BitmaskProgramExecutor;

protected:
    virtual void executeMemInstruction(const Instruction& instruction) override;
    virtual void executeMaskInstruction(const Instruction& instruction) override;

private:
    std::vector<size_t> m_floatingDigits;

    std::vector<uint64_t> getAllAddresses(uint64_t baseAddress) const;
    void getAllAddressesRecursive(uint64_t baseAddress, size_t floatingDigitsIndex, std::vector<uint64_t>& allAddresses) const;
};

}
}
}
