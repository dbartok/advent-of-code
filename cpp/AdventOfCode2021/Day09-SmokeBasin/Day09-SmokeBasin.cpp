#include "Day09-SmokeBasin.h"

#include "HeightmapAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <iterator>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day09
{

HeightmapRow parseHeightmapLine(const std::string& heightmapLine)
{
    HeightmapRow heightmapRow;

    std::transform(heightmapLine.cbegin(), heightmapLine.cend(), std::back_inserter(heightmapRow), [](const char c)
                   {
                       return c - '0';
                   });

    return heightmapRow;
}

Heightmap parseHeightmapLines(const std::vector<std::string>& heightmapLines)
{
    Heightmap heightmap;

    for (const auto& line : heightmapLines)
    {
        HeightmapRow heightmapRow = parseHeightmapLine(line);
        heightmap.push_back(std::move(heightmapRow));
    }

    return heightmap;
}

int sumOfRiskLevelsOfAllLowPoints(const std::vector<std::string>& heightmapLines)
{
    Heightmap heightmap = parseHeightmapLines(heightmapLines);
    HeightmapAnalyzer heightmapAnalyzer{std::move(heightmap)};
    return heightmapAnalyzer.getSumOfRiskLevelsOfAllLowPoints();
}

int multipleOfThreeLargestBasinSizes(const std::vector<std::string>& heightmapLines)
{
    Heightmap heightmap = parseHeightmapLines(heightmapLines);
    HeightmapAnalyzer heightmapAnalyzer{std::move(heightmap)};
    return heightmapAnalyzer.getMultipleOfThreeLargestBasinSizes();
}

}
}
}