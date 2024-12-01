#include "NanobotsAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day23
{

NanobotsAnalyzer::NanobotsAnalyzer(std::vector<Nanobot> nanobots)
    : m_nanobots{std::move(nanobots)}
{

}

unsigned NanobotsAnalyzer::numNanobotsInStrongestRange() const
{
    const Nanobot strongestNanobot = *std::max_element(m_nanobots.cbegin(), m_nanobots.cend(), [](const Nanobot& lhs, const Nanobot& rhs)
                                                        {
                                                            return lhs.range < rhs.range;
                                                        });

    unsigned numInRange = std::count_if(m_nanobots.cbegin(), m_nanobots.cend(), [&strongestNanobot](const Nanobot& otherNanobot)
                                        {
                                            CoordinateType manhattanDistance = getManhattanDistance(strongestNanobot.position, otherNanobot.position);
                                            return manhattanDistance <= strongestNanobot.range;
                                        });

    return numInRange;
}

int NanobotsAnalyzer::lowestDistanceFromOriginWithMostNanobots() const
{
    CoordinateType cubeSize = 200'000'000;
    Vector3D searchPos{0, 0, 0};

    while (true)
    {
        unsigned maxNanobotCountForCube = 0;
        Vector3D bestRefinedSearchPos{0, 0, 0};

        for (const auto& currentRefinedSearchPos : getRefinedSearchPositions(searchPos, cubeSize))
        {
            unsigned currentNanobotCountForCube = numNanobotsThatHaveCubeInRange(currentRefinedSearchPos, cubeSize);

            bool isCloserToOrigin = getManhattanDistance(currentRefinedSearchPos, ORIGIN) < getManhattanDistance(bestRefinedSearchPos, ORIGIN);
            bool isNewBestPos = (currentNanobotCountForCube > maxNanobotCountForCube) || (currentNanobotCountForCube == maxNanobotCountForCube && isCloserToOrigin);
            if (isNewBestPos)
            {
                maxNanobotCountForCube = currentNanobotCountForCube;
                bestRefinedSearchPos = currentRefinedSearchPos;
            }
        }

        if (cubeSize == 1)
        {
            return getManhattanDistance(bestRefinedSearchPos, ORIGIN);
        }

        searchPos = bestRefinedSearchPos;
        cubeSize /= 2;
    }
}

unsigned NanobotsAnalyzer::numNanobotsThatHaveCubeInRange(const Vector3D& position, CoordinateType cubeSize) const
{
    unsigned numNanobots = std::count_if(m_nanobots.cbegin(), m_nanobots.cend(), [&position, cubeSize](const Nanobot& nanobot)
                                            {
                                                CoordinateType manhattanDistance = getManhattanDistance(position, nanobot.position);
                                                return manhattanDistance < nanobot.range + cubeSize;
                                            });

    return numNanobots;
}

std::vector<Vector3D> NanobotsAnalyzer::getRefinedSearchPositions(const Vector3D& searchPos, CoordinateType cubeSize) const
{
    std::vector<Vector3D> refinedSearchPositions;

    const CoordinateType searchAreaRadius = 2 * cubeSize;

    for (CoordinateType i = searchPos[0] - searchAreaRadius; i <= searchPos[0] + searchAreaRadius; i += cubeSize)
    {
        for (CoordinateType j = searchPos[1] - searchAreaRadius; j <= searchPos[1] + searchAreaRadius; j += cubeSize)
        {
            for (CoordinateType k = searchPos[2] - searchAreaRadius; k <= searchPos[2] + searchAreaRadius; k += cubeSize)
            {
                refinedSearchPositions.emplace_back(i, j, k);
            }
        }
    }

    return refinedSearchPositions;
}

CoordinateType NanobotsAnalyzer::getManhattanDistance(const Vector3D& position1, const Vector3D& position2)
{
    auto distanceVector = position1 - position2;
    return distanceVector.cwiseAbs().sum();
}

}
}
}
