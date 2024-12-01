#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <array>
#include <functional>
#include <set>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day16
{

using Registers = std::array<unsigned, 6>;

struct Instruction
{
    unsigned opcode;
    unsigned a;
    unsigned b;
    unsigned c;

    Instruction(unsigned opcode, unsigned a, unsigned b, unsigned c)
        : opcode{opcode}
        , a{a}
        , b{b}
        , c{c}
    {

    }
};

using OpcodeStringSet = std::set<std::string>;
using OpcodeToOpcodeString = std::unordered_map<unsigned, std::string>;

class InstructionEvaluator
{
private:
    using AssemblyFunc = std::function<void()>;

public:
    InstructionEvaluator(Instruction instruction, Registers registers);

    Registers evaluateAs(const std::string& opcodeString);

    OpcodeStringSet getAllOpcodeStrings() const;

private:
    Instruction m_instruction;
    Registers m_registers;
    std::unordered_map<std::string, AssemblyFunc> m_opcodeStringToAssemblyFunc;

    void addr();
    void addi();
    void mulr();
    void muli();
    void banr();
    void bani();
    void borr();
    void bori();
    void setr();
    void seti();
    void gtir();
    void gtri();
    void gtrr();
    void eqir();
    void eqri();
    void eqrr();
};

}
}
}
