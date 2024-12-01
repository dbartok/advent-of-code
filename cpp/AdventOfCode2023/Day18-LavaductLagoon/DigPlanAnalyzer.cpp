#include "DigPlanAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day18
{

DigPlanAnalyzer::DigPlanAnalyzer(std::vector<Instruction> instructions)
    : m_instructions{std::move(instructions)}
{
    Vector2D currentPerimeterPoint{0, 0};
    for (const auto& instruction : m_instructions)
    {
        m_perimeterPoints.push_back(currentPerimeterPoint);
        currentPerimeterPoint += instruction.numTiles * instruction.direction;
    }
}

int64_t DigPlanAnalyzer::getAmountOfLavaHeld() const
{
    const int64_t area = getArea();
    const int64_t perimeter = getPerimeter();

    // Pick's theorem: A = i + b / 2 - 1
    // Where A is the area, i is the number of interior points, b is the number of boundary points
    // Solving for i:
    // i = A - b / 2 + 1
    const int64_t numInternalPoints = area - perimeter / 2 + 1;

    return numInternalPoints + perimeter;
}

int64_t DigPlanAnalyzer::getArea() const
{
    int64_t twiceArea = 0;

    // Apply the Shoelace formula
    for (size_t i = 0; i < m_perimeterPoints.size(); ++i)
    {
        const Vector2D& currentPerimeterPoint = m_perimeterPoints.at(i);
        const Vector2D& nextPerimeterPoint = m_perimeterPoints.at((i + 1) % m_perimeterPoints.size());

        Matrix2D currentMatrix;
        currentMatrix <<
            currentPerimeterPoint.x(), nextPerimeterPoint.x(),
            currentPerimeterPoint.y(), nextPerimeterPoint.y();

        twiceArea += currentMatrix.determinant();
    }

    return twiceArea / 2;
}

int64_t DigPlanAnalyzer::getPerimeter() const
{
    return std::accumulate(m_instructions.cbegin(), m_instructions.cend(), 0ll, [](int64_t acc, const auto& instruction)
                            {
                                return acc + instruction.numTiles;
                            });
}

}
}
}
