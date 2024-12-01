#pragma once

#include "LineSegment.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day05
{

class HydrothermalVentAnalyzer
{
public:
    HydrothermalVentAnalyzer(std::vector<LineSegment> ventLineSegments);

    void analyzeOverlaps();

    int getNumPointsWithOverlap() const;

private:
    std::vector<LineSegment> m_ventLineSegments;
    std::unordered_map<Vector2D, int, Vector2DHash> m_coordinatesToNumVents;

    void markCoveredPoints(const LineSegment& ventLineSegment);
};

}
}
}
