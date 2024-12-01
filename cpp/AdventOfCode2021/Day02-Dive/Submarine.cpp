#include "Submarine.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day02
{

Submarine::Submarine(std::vector<Instruction> instructions)
    : m_instructions(std::move(instructions))
{

}

void Submarine::moveToFinalPosition()
{
    for (const auto& instruction : m_instructions)
    {
        executeInstruction(instruction);
    }
}

int Submarine::getHorizontalPositionAndDepthMultiplied() const
{
    return m_horizontalPosition * m_depth;
}

Submarine::~Submarine()
{

}

SimpleCourseSubmarine::~SimpleCourseSubmarine()
{

}

void SimpleCourseSubmarine::executeInstruction(const Instruction& instruction)
{
    if (instruction.direction == Direction::UP)
    {
        m_depth -= instruction.length;
    }
    else if (instruction.direction == Direction::DOWN)
    {
        m_depth += instruction.length;
    }
    else if (instruction.direction == Direction::FORWARD)
    {
        m_horizontalPosition += instruction.length;
    }
    else
    {
        throw std::runtime_error("Invalid direction: " + std::to_string(static_cast<int>(instruction.direction)));
    }
}

AdjustedCourseSubmarine::~AdjustedCourseSubmarine()
{

}

void AdjustedCourseSubmarine::executeInstruction(const Instruction& instruction)
{
    if (instruction.direction == Direction::UP)
    {
        m_aim -= instruction.length;
    }
    else if (instruction.direction == Direction::DOWN)
    {
        m_aim += instruction.length;
    }
    else if (instruction.direction == Direction::FORWARD)
    {
        m_horizontalPosition += instruction.length;
        m_depth += m_aim * instruction.length;
    }
    else
    {
        throw std::runtime_error("Invalid direction: " + std::to_string(static_cast<int>(instruction.direction)));
    }
}

}
}
}
