#include "GalaxyImageAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char GALAXY = '#';

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day11
{

GalaxyImageAnalyzer::GalaxyImageAnalyzer(std::vector<std::string> image, int expansionRate)
    : m_image{std::move(image)}
    , m_height{m_image.size()}
    , m_width{m_image.front().size()}
    , m_expansionRate{expansionRate}
{

}

void GalaxyImageAnalyzer::analyze()
{
    for (int j = 0; j < m_height; ++j)
    {
        m_emptyRowCoordinates.insert(j);
    }

    for (int i = 0; i < m_height; ++i)
    {
        m_emptyColumnCoordinates.insert(i);
    }

    for (int i = 0; i < m_width; ++i)
    {
        for (int j = 0; j < m_height; ++j)
        {
            if (m_image.at(j).at(i) == GALAXY)
            {
                m_galaxyCoordinates.push_back({i, j});
                m_emptyRowCoordinates.erase(j);
                m_emptyColumnCoordinates.erase(i);
            }
        }
    }
}

int64_t GalaxyImageAnalyzer::getSumOfAllShortestPathsBetweenAllPairs() const
{
    int64_t sumOfAllShortestPathsBetweenAllPairs = 0;

    for (auto firstGalaxyCoordinatesIter = m_galaxyCoordinates.cbegin(); firstGalaxyCoordinatesIter != m_galaxyCoordinates.cend(); ++firstGalaxyCoordinatesIter)
    {
        for (auto secondGalaxyCoordinatesIter = firstGalaxyCoordinatesIter + 1; secondGalaxyCoordinatesIter != m_galaxyCoordinates.cend(); ++secondGalaxyCoordinatesIter)
        {
            const int distance = getDistanceBetween(*firstGalaxyCoordinatesIter, *secondGalaxyCoordinatesIter);
            sumOfAllShortestPathsBetweenAllPairs += distance;
        }
    }

    return sumOfAllShortestPathsBetweenAllPairs;
}

int GalaxyImageAnalyzer::getDistanceBetween(const Coordinates& firstPoint, const Coordinates& secondPoint) const
{
    int numStepsWithExtendedLength = 0;

    for (int j = std::min(firstPoint.second, secondPoint.second); j <= std::max(firstPoint.second, secondPoint.second); ++j)
    {
        if (m_emptyRowCoordinates.count(j))
        {
            ++numStepsWithExtendedLength;
        }
    }

    for (int i = std::min(firstPoint.first, secondPoint.first); i <= std::max(firstPoint.first, secondPoint.first); ++i)
    {
        if (m_emptyColumnCoordinates.count(i))
        {
            ++numStepsWithExtendedLength;
        }
    }

    return std::abs(firstPoint.first - secondPoint.first) + std::abs(firstPoint.second - secondPoint.second) + numStepsWithExtendedLength * (m_expansionRate - 1);
}

}
}
}
