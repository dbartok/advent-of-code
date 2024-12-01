#include "InstructionEvaluator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day16
{
InstructionEvaluator::InstructionEvaluator(Instruction instruction, Registers registers)
    : m_instruction{std::move(instruction)}
    , m_registers{std::move(registers)}
{
    m_opcodeStringToAssemblyFunc =
    {
        {"addr", [this]() {this->addr(); }},
        {"addi", [this]() {this->addi(); }},
        {"mulr", [this]() {this->mulr(); }},
        {"muli", [this]() {this->muli(); }},
        {"banr", [this]() {this->banr(); }},
        {"bani", [this]() {this->bani(); }},
        {"borr", [this]() {this->borr(); }},
        {"bori", [this]() {this->bori(); }},
        {"setr", [this]() {this->setr(); }},
        {"seti", [this]() {this->seti(); }},
        {"gtir", [this]() {this->gtir(); }},
        {"gtri", [this]() {this->gtri(); }},
        {"gtrr", [this]() {this->gtrr(); }},
        {"eqir", [this]() {this->eqir(); }},
        {"eqri", [this]() {this->eqri(); }},
        {"eqrr", [this]() {this->eqrr(); }},
    };
}

Registers InstructionEvaluator::evaluateAs(const std::string& opcodeString)
{
    Registers registersSnapshot{m_registers};

    m_opcodeStringToAssemblyFunc.at(opcodeString)();

    std::swap(registersSnapshot, m_registers);

    return registersSnapshot;
}

OpcodeStringSet InstructionEvaluator::getAllOpcodeStrings() const
{
    OpcodeStringSet allOpcodeStrings;

    std::transform(m_opcodeStringToAssemblyFunc.cbegin(), m_opcodeStringToAssemblyFunc.cend(), std::inserter(allOpcodeStrings, allOpcodeStrings.begin()),
                    [](const auto& elem)
                    {
                        return elem.first;
                    });

    return allOpcodeStrings;
}

void InstructionEvaluator::addr()
{
    m_registers[m_instruction.c] = m_registers[m_instruction.a] + m_registers[m_instruction.b];
}

void InstructionEvaluator::addi()
{
    m_registers[m_instruction.c] = m_registers[m_instruction.a] + m_instruction.b;
}

void InstructionEvaluator::mulr()
{
    m_registers[m_instruction.c] = m_registers[m_instruction.a] * m_registers[m_instruction.b];
}

void InstructionEvaluator::muli()
{
    m_registers[m_instruction.c] = m_registers[m_instruction.a] * m_instruction.b;
}

void InstructionEvaluator::banr()
{
    m_registers[m_instruction.c] = m_registers[m_instruction.a] & m_registers[m_instruction.b];
}

void InstructionEvaluator::bani()
{
    m_registers[m_instruction.c] = m_registers[m_instruction.a] & m_instruction.b;
}

void InstructionEvaluator::borr()
{
    m_registers[m_instruction.c] = m_registers[m_instruction.a] | m_registers[m_instruction.b];
}

void InstructionEvaluator::bori()
{
    m_registers[m_instruction.c] = m_registers[m_instruction.a] | m_instruction.b;
}

void InstructionEvaluator::setr()
{
    m_registers[m_instruction.c] = m_registers[m_instruction.a];
}

void InstructionEvaluator::seti()
{
    m_registers[m_instruction.c] = m_instruction.a;
}

void InstructionEvaluator::gtir()
{
    m_registers[m_instruction.c] = (m_instruction.a > m_registers[m_instruction.b]) ? 1u : 0u;
}

void InstructionEvaluator::gtri()
{
    m_registers[m_instruction.c] = (m_registers[m_instruction.a] > m_instruction.b) ? 1u : 0u;
}

void InstructionEvaluator::gtrr()
{
    m_registers[m_instruction.c] = (m_registers[m_instruction.a] > m_registers[m_instruction.b]) ? 1u : 0u;
}

void InstructionEvaluator::eqir()
{
    m_registers[m_instruction.c] = (m_instruction.a == m_registers[m_instruction.b]) ? 1u : 0u;
}

void InstructionEvaluator::eqri()
{
    m_registers[m_instruction.c] = (m_registers[m_instruction.a] == m_instruction.b) ? 1u : 0u;
}

void InstructionEvaluator::eqrr()
{
    m_registers[m_instruction.c] = (m_registers[m_instruction.a] == m_registers[m_instruction.b]) ? 1u : 0u;
}

}
}
}
