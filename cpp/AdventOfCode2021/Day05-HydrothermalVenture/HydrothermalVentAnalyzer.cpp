#include "HydrothermalVentAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day05
{

HydrothermalVentAnalyzer::HydrothermalVentAnalyzer(std::vector<LineSegment> ventLineSegments)
    : m_ventLineSegments{std::move(ventLineSegments)}
{

}

void HydrothermalVentAnalyzer::analyzeOverlaps()
{
    for (const auto& ventLineSegment : m_ventLineSegments)
    {
        markCoveredPoints(ventLineSegment);
    }
}

int HydrothermalVentAnalyzer::getNumPointsWithOverlap() const
{
    return std::count_if(m_coordinatesToNumVents.cbegin(), m_coordinatesToNumVents.cend(), [](const auto& elem)
                            {
                                return elem.second > 1;
                            });
}

void HydrothermalVentAnalyzer::markCoveredPoints(const LineSegment& ventLineSegment)
{
    std::vector<Vector2D> coveredPoints = ventLineSegment.getCoveredPoints();

    for (const auto& coveredPoint : coveredPoints)
    {
        ++m_coordinatesToNumVents[coveredPoint];
    }
}

}
}
}
