#include "Day14-DockingData.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>

#include <unordered_map>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

enum class InstructionType
{
    MASK,
    MEM,
};

struct Instruction
{
    Instruction(InstructionType type, std::string arg, uint64_t addr)
        : type{type}
        , arg{std::move(arg)}
        , addr{addr}
    {

    }

    Instruction(InstructionType type, std::string arg)
        : type{type}
        , arg{std::move(arg)}
        , addr{boost::none}
    {

    }

    InstructionType type;
    std::string arg;
    boost::optional<uint64_t> addr;
};

class BitmaskProgramExecutor
{
public:
    BitmaskProgramExecutor(std::vector<Instruction> instructions)
        : m_instructions{std::move(instructions)}
    {

    }

    void execute()
    {
        for (const auto& instruction : m_instructions)
        {
            executeInstruction(instruction);
        }
    }

    uint64_t getSumOfValuesInMemory() const
    {
        return std::accumulate(m_memoryLocationToValue.cbegin(), m_memoryLocationToValue.cend(), 0ull, [](auto acc, const auto& elem)
                               {
                                   return acc + elem.second;
                               });
    }

private:
    std::vector<Instruction> m_instructions;

    uint64_t m_andBitmask = ~0ull;
    uint64_t m_orBitmask = 0ull;
    std::unordered_map<uint64_t, uint64_t> m_memoryLocationToValue;

    void executeInstruction(const Instruction& instruction)
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

    void executeMemInstruction(const Instruction& instruction)
    {
        uint64_t value = std::stoull(instruction.arg);
        value &= m_andBitmask;
        value |= m_orBitmask;

        m_memoryLocationToValue[instruction.addr.get()] = value;
    }

    void executeMaskInstruction(const Instruction& instruction)
    {
        std::string orBitmaskString = instruction.arg;
        boost::replace_all(orBitmaskString, "X", "0");
        m_orBitmask = std::stoull(orBitmaskString, nullptr, 2);

        std::string andBitmaskString = instruction.arg;
        boost::replace_all(andBitmaskString, "X", "1");
        m_andBitmask = std::stoull(andBitmaskString, nullptr, 2);
    }

};

Instruction parseInstruction(const std::string& instruction)
{
    std::vector<std::string> tokens;
    if (instruction.substr(0, 3) == "mem")
    {
        boost::split(tokens, instruction, boost::is_any_of("[]= "), boost::token_compress_on);
        return Instruction{InstructionType::MEM, tokens.at(2), std::stoull(tokens.at(1))};
    }
    else
    {
        boost::split(tokens, instruction, boost::is_any_of("= "), boost::token_compress_on);
        return Instruction{InstructionType::MASK, tokens.at(1)};
    }
}

std::vector<Instruction> parseInstructions(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions;

    for (const auto& line : instructionLines)
    {
        Instruction instruction = parseInstruction(line);
        instructions.push_back(std::move(instruction));
    }

    return instructions;
}

uint64_t sumOfValuesInMemoryAfterCompletion(const std::vector<std::string>& instructionLines)
{
    std::vector<Instruction> instructions = parseInstructions(instructionLines);
    BitmaskProgramExecutor bitmaskProgramExecutor{std::move(instructions)};
    bitmaskProgramExecutor.execute();
    return bitmaskProgramExecutor.getSumOfValuesInMemory();
}

}
