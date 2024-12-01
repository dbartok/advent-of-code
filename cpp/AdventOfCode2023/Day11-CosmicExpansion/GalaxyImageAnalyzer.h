#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int DEFAULT_EXPANSION_RATE = 2;

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day11
{

class GalaxyImageAnalyzer
{
public:
    GalaxyImageAnalyzer(std::vector<std::string> image, int expansionRate = DEFAULT_EXPANSION_RATE);

    void analyze();

    int64_t getSumOfAllShortestPathsBetweenAllPairs() const;

private:
    using Coordinates = std::pair<int, int>;

    std::vector<std::string> m_image;
    size_t m_width;
    size_t m_height;
    int m_expansionRate;

    std::vector<Coordinates> m_galaxyCoordinates;
    std::unordered_set<int> m_emptyRowCoordinates;
    std::unordered_set<int> m_emptyColumnCoordinates;

    int getDistanceBetween(const Coordinates& firstPoint, const Coordinates& secondPoint) const;
};

}
}
}
