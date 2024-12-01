#include "BitmaskProgramExecutor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day14
{

Instruction::Instruction(InstructionType type, std::string arg, uint64_t addr)
    : type{type}
    , arg{std::move(arg)}
    , addr{addr}
{

}

Instruction::Instruction(InstructionType type, std::string arg)
    : type{type}
    , arg{std::move(arg)}
    , addr{boost::none}
{

}

BitmaskProgramExecutor::BitmaskProgramExecutor(std::vector<Instruction> instructions)
    : m_instructions{std::move(instructions)}
{

}

void BitmaskProgramExecutor::execute()
{
    for (const auto& instruction : m_instructions)
    {
        executeInstruction(instruction);
    }
}

uint64_t BitmaskProgramExecutor::getSumOfValuesInMemory() const
{
    return std::accumulate(m_memoryLocationToValue.cbegin(), m_memoryLocationToValue.cend(), 0ull, [](auto acc, const auto& elem)
                           {
                               return acc + elem.second;
                           });
}

void BitmaskProgramExecutor::executeMemInstruction(const Instruction& instruction)
{
    uint64_t value = std::stoull(instruction.arg);
    value &= m_andBitmask;
    value |= m_orBitmask;

    m_memoryLocationToValue[instruction.addr.get()] = value;
}

void BitmaskProgramExecutor::executeMaskInstruction(const Instruction& instruction)
{
    std::string orBitmaskString = instruction.arg;
    boost::replace_all(orBitmaskString, "X", "0");
    m_orBitmask = std::stoull(orBitmaskString, nullptr, 2);

    std::string andBitmaskString = instruction.arg;
    boost::replace_all(andBitmaskString, "X", "1");
    m_andBitmask = std::stoull(andBitmaskString, nullptr, 2);
}

void BitmaskProgramExecutor::executeInstruction(const Instruction& instruction)
{
    if (instruction.type == InstructionType::MEM)
    {
        executeMemInstruction(instruction);
    }
    else
    {
        executeMaskInstruction(instruction);
    }
}

void BitmaskDecoderProgramExecutor::executeMemInstruction(const Instruction& instruction)
{
    uint64_t baseAddress = instruction.addr.get();
    baseAddress |= m_orBitmask;

    std::vector<uint64_t> addresses = getAllAddresses(baseAddress);
    uint64_t value = std::stoull(instruction.arg);

    for (auto address : addresses)
    {
        m_memoryLocationToValue[address] = value;
    }
}

void BitmaskDecoderProgramExecutor::executeMaskInstruction(const Instruction& instruction)
{
    BitmaskProgramExecutor::executeMaskInstruction(instruction);

    std::string digitToValue = instruction.arg;
    std::reverse(digitToValue.begin(), digitToValue.end());
    m_floatingDigits.clear();
    for (size_t i = 0; i < digitToValue.size(); ++i)
    {
        if (digitToValue[i] == 'X')
        {
            m_floatingDigits.push_back(i);
        }
    }
}

std::vector<uint64_t> BitmaskDecoderProgramExecutor::getAllAddresses(uint64_t baseAddress) const
{
    std::vector<uint64_t> allAddresses;
    getAllAddressesRecursive(baseAddress, 0, allAddresses);
    return allAddresses;
}

void BitmaskDecoderProgramExecutor::getAllAddressesRecursive(uint64_t baseAddress, size_t floatingDigitsIndex, std::vector<uint64_t>& allAddresses) const
{
    if (floatingDigitsIndex >= m_floatingDigits.size())
    {
        allAddresses.push_back(baseAddress);
        return;
    }

    size_t floatingIndex = m_floatingDigits.at(floatingDigitsIndex);

    uint64_t baseAddressLower = baseAddress;
    baseAddressLower &= ~(1ull << floatingIndex);
    getAllAddressesRecursive(baseAddressLower, floatingDigitsIndex + 1, allAddresses);

    uint64_t baseAddressHigher = baseAddress;
    baseAddressHigher |= (1ull << floatingIndex);
    getAllAddressesRecursive(baseAddressHigher, floatingDigitsIndex + 1, allAddresses);
}

}
}
}
