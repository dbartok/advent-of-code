#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <Eigen/Dense>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day10
{

using Coordinates = std::pair<int, int>;
using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

using Vector2D = Eigen::Matrix<int, 2, 1>;

class AsteroidMap
{
public:
    AsteroidMap(CoordinatesSet asteroidCoordinatesSet);

    unsigned getMaxNumAsteroidsDetected() const;

    std::vector<Coordinates> vaporize();

private:
    CoordinatesSet m_asteroidCoordinatesSet;
    Coordinates m_locatorPosition;
    Vector2D m_laserVector;

    std::vector<Coordinates> m_vaporizationOrder;

    Coordinates determineLocatorPosition() const;
    unsigned getNumAsteroidsDetected(const Coordinates& stationPos) const;
    bool isThereDirectLineOfSight(const Coordinates& fromCoordinates, const Coordinates& toCoordinates) const;

    void vaporizeNextAsteroid();
    Coordinates findNextAsteroidToVaporize() const;
    double getLaserAngleToAsteroid(const Coordinates& asteroidCoordinates) const;
};

}
}
}
