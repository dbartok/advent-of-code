#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day23
{

using CoordinateType = int;
using Vector3D = Eigen::Matrix<CoordinateType, 3, 1>;

const Vector3D ORIGIN = {0, 0, 0};

struct Nanobot
{
    Vector3D position;
    CoordinateType range;

    Nanobot(Vector3D position, CoordinateType range)
        : position{std::move(position)}
        , range(range)
    {

    }
};

class NanobotsAnalyzer
{
public:
    NanobotsAnalyzer(std::vector<Nanobot> nanobots);

    unsigned numNanobotsInStrongestRange() const;
    int lowestDistanceFromOriginWithMostNanobots() const;

private:
    std::vector<Nanobot> m_nanobots;

    unsigned numNanobotsThatHaveCubeInRange(const Vector3D& position, CoordinateType cubeSize) const;
    std::vector<Vector3D> getRefinedSearchPositions(const Vector3D& searchPos, CoordinateType cubeSize) const;

    static CoordinateType getManhattanDistance(const Vector3D& position1, const Vector3D& position2);
};

}
}
}
