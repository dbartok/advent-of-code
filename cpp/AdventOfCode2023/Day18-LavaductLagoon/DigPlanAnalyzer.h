#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/dense>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day18
{

using Vector2D = Eigen::Matrix<int64_t, 2, 1>;
using Matrix2D = Eigen::Matrix<int64_t, 2, 2>;

struct Instruction
{
    Vector2D direction;
    int numTiles;
};

class DigPlanAnalyzer
{
public:
    DigPlanAnalyzer(std::vector<Instruction> instructions);

    int64_t getAmountOfLavaHeld() const;

private:
    std::vector<Instruction> m_instructions;
    std::vector<Vector2D> m_perimeterPoints;

    int64_t getArea() const;
    int64_t getPerimeter() const;
};

}
}
}
