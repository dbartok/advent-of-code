#include "LineSegment.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/integer/common_factor.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day05
{

LineSegment::LineSegment(Vector2D start, Vector2D end)
    : m_start{std::move(start)}
    , m_end{std::move(end)}
{

}

bool LineSegment::isAxisParallel() const
{
    return m_start.x() == m_end.x() || m_start.y() == m_end.y();
}

std::vector<Vector2D> LineSegment::getCoveredPoints() const
{
    const Vector2D differenceVector = m_end - m_start;
    const Vector2D differenceVectorAbs = differenceVector.cwiseAbs();

    const int numStepsFromStartToEnd = boost::integer::gcd(differenceVectorAbs[0], differenceVectorAbs[1]);

    const Vector2D stepVector = differenceVector / numStepsFromStartToEnd;

    std::vector<Vector2D> coveredPoints;
    for (Vector2D innerPointVector = m_start; ; innerPointVector += stepVector)
    {
        coveredPoints.push_back(innerPointVector);

        if (innerPointVector == m_end)
        {
            break;
        }
    }

    return coveredPoints;
}

}
}
}
