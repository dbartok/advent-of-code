#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <Eigen/dense>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day24
{

using PreciseFloat = boost::multiprecision::cpp_dec_float_100;
using Vector3D = Eigen::Matrix<PreciseFloat, 3, 1>;

struct Hailstone
{
    Vector3D position;
    Vector3D velocity;
};

class HailstoneSystem
{
public:
    HailstoneSystem(std::vector<Hailstone> hailstones);

    void calculateRockStartingPositionForRockVelocityXY(const Vector3D rockVelocityXY);

    int getNumXYIntersectionsWithinTestArea(double testAreaMin, double testAreaMax) const;
    boost::optional<Vector3D> getRockStartingPosition() const;

private:
    std::vector<Hailstone> m_hailstones;

    boost::optional<Vector3D> m_rockStartingPosition;

    void adjustVelocitiesForRockVelocity(const Vector3D rockVelocity);

    boost::optional<Vector3D> getCommonXYIntersection() const;
    boost::optional<Vector3D> getXYIntersection(const Hailstone& firstHailstone, const Hailstone& secondHailstone) const;
    boost::optional<PreciseFloat> getCommonRockVelocityZ(const Vector3D& commonXYIntersection) const;
    PreciseFloat getRockVelocityZ(const Hailstone& firstHailstone, const Hailstone& secondHailstone, const Vector3D& commonXYIntersection) const;
    PreciseFloat getRockStartingPositionZ(const Vector3D& commonXYIntersection, PreciseFloat rockVelocityZ) const;

    static PreciseFloat getTimeUntilXYPosition(const Hailstone& hailstone, const Vector3D& position);
};

}
}
}
