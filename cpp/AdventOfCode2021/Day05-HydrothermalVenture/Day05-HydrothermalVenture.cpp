#include "Day05-HydrothermalVenture.h"

#include "LineSegment.h"
#include "HydrothermalVentAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day05
{

Vector2D parseCoordinatesString(const std::string& coordinatesString)
{
    std::vector<std::string> tokens;
    boost::split(tokens, coordinatesString, boost::is_any_of(","));

    return Vector2D{std::stoi(tokens.at(0)), std::stoi(tokens.at(1))};
}

LineSegment parseVentLine(const std::string& ventLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, ventLine, boost::is_any_of(" ->"), boost::token_compress_on);

    Vector2D start = parseCoordinatesString(tokens.at(0));
    Vector2D end = parseCoordinatesString(tokens.at(1));

    return LineSegment{std::move(start), std::move(end)};
}


std::vector<LineSegment> parseVentLines(const std::vector<std::string>& ventLines)
{
    std::vector<LineSegment> ventLineSegments;

    for (const auto& line : ventLines)
    {
        LineSegment ventLineSegment = parseVentLine(line);
        ventLineSegments.push_back(std::move(ventLineSegment));
    }

    return ventLineSegments;
}

int numPointsWhereHorizontalOrVerticalLinesOverlap(const std::vector<std::string>& ventLines)
{
    std::vector<LineSegment> ventLineSegments = parseVentLines(ventLines);
    std::vector<LineSegment> axisParallelVentLineSegments;
    std::copy_if(ventLineSegments.cbegin(), ventLineSegments.cend(), std::back_inserter(axisParallelVentLineSegments), [](const auto& lineSegment)
                 {
                     return lineSegment.isAxisParallel();
                 });

    HydrothermalVentAnalyzer hydrothermalVentAnalyzer{axisParallelVentLineSegments};
    hydrothermalVentAnalyzer.analyzeOverlaps();
    return hydrothermalVentAnalyzer.getNumPointsWithOverlap();
}

int numPointsWhereLinesOverlap(const std::vector<std::string>& ventLines)
{
    std::vector<LineSegment> ventLineSegments = parseVentLines(ventLines);
    HydrothermalVentAnalyzer hydrothermalVentAnalyzer{ventLineSegments};
    hydrothermalVentAnalyzer.analyzeOverlaps();
    return hydrothermalVentAnalyzer.getNumPointsWithOverlap();
}

}
}
}