#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day02
{

enum class Direction
{
    UP,
    DOWN,
    FORWARD,
};

struct Instruction
{
    Direction direction;
    int length;
};

class Submarine
{
public:
    Submarine(std::vector<Instruction> instructions);

    void moveToFinalPosition();

    int getHorizontalPositionAndDepthMultiplied() const;

    virtual ~Submarine();

protected:
    int m_horizontalPosition = 0;
    int m_depth = 0;

    virtual void executeInstruction(const Instruction& instruction) = 0;

private:
    std::vector<Instruction> m_instructions;
};

class SimpleCourseSubmarine : public Submarine
{
public:
    using Submarine::Submarine;

    virtual ~SimpleCourseSubmarine();

protected:
    void executeInstruction(const Instruction& instruction) override;
};

class AdjustedCourseSubmarine : public Submarine
{
public:
    using Submarine::Submarine;

    virtual ~AdjustedCourseSubmarine();

protected:
    void executeInstruction(const Instruction& instruction) override;

private:
    int m_aim = 0;
};

}
}
}
