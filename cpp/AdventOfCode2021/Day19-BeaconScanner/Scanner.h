#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/dense>

#include <vector>
#include <set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day19
{

using Vector3D = Eigen::RowVector3i;
using Matrix3D = Eigen::Matrix3i;

struct Vector3DCmp
{
    bool operator()(const Vector3D& lhs, const Vector3D& rhs) const
    {
        return std::lexicographical_compare(
            lhs.data(), lhs.data() + lhs.size(),
            rhs.data(), rhs.data() + rhs.size());
    }
};

using Vector3DSet = std::set<Vector3D, Vector3DCmp>;

class Scanner
{
public:
    Scanner(int id, std::vector<Vector3D> beaconPositions);

    void applyBaseTransform(const Matrix3D& baseTransformVector);
    void applyOffset(const Vector3D& offset);

    Vector3DSet getPossibleOffsetsFrom(const Scanner& other) const;
    unsigned getNumOverlappingBeacons(const Scanner& other) const;
    Vector3DSet getBeaconPositionUnion(Vector3DSet otherBeaconPositions) const;
    unsigned getManhattanDistanceFrom(const Scanner& other) const;
    int getId();
    const Vector3D& getOffset() const;

    bool operator==(const Scanner& other) const;

private:
    std::vector<Vector3D> m_beaconPositions;
    int m_id;
    Vector3D m_offset{0, 0, 0};
};

}
}
}
