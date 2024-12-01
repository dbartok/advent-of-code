#include "CaveMap.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day22
{

CaveMap::CaveMap(unsigned depth, Coordinates targetCoordinates)
    : m_depth{depth}
    , m_targetCoordinates{std::move(targetCoordinates)}
{

}

unsigned CaveMap::calculateRiskLevelOfArea()
{
    unsigned totalRiskLevelOfArea = 0;

    for (size_t j = 0; j <= m_targetCoordinates.first; ++j)
    {
        for (size_t i = 0; i <= m_targetCoordinates.second; ++i)
        {
            unsigned riskLevel = getRiskLevelAt({j, i});
            totalRiskLevelOfArea += riskLevel;
        }
    }
    return totalRiskLevelOfArea;
}

unsigned CaveMap::getRiskLevelAt(const Coordinates& coordinates)
{
    return getErosionLevelAt(coordinates) % 3;
}

const Coordinates& CaveMap::getTargetCoordinates() const
{
    return m_targetCoordinates;
}

unsigned CaveMap::getErosionLevelAt(const Coordinates& coordinates)
{
    unsigned erosionLevel = 0;

    auto findResult = m_erosionLevelCache.find(coordinates);
    if (findResult != m_erosionLevelCache.end())
    {
        erosionLevel = findResult->second;
    }
    else
    {
        erosionLevel = calculateErosionLevelAt(coordinates);
        m_erosionLevelCache.emplace(coordinates, erosionLevel);
    }

    return erosionLevel;
}

unsigned CaveMap::calculateErosionLevelAt(const Coordinates& coordinates)
{
    unsigned geologicalIndex = 0;

    if (coordinates.first == 0 && coordinates.second == 0)
    {
        geologicalIndex = 0;
    }
    else if (coordinates == m_targetCoordinates)
    {
        geologicalIndex = 0;
    }
    else if (coordinates.first == 0)
    {
        geologicalIndex = coordinates.second * 16807;
    }
    else if (coordinates.second == 0)
    {
        geologicalIndex = coordinates.first * 48271;
    }
    else
    {
        unsigned erosionLevelToLeft = getErosionLevelAt({coordinates.first, coordinates.second - 1});
        unsigned erosionLevelToUpwards = getErosionLevelAt({coordinates.first - 1, coordinates.second});

        geologicalIndex = erosionLevelToLeft * erosionLevelToUpwards;
    }

    return (geologicalIndex + m_depth) % 20183;
}

}
}
}
