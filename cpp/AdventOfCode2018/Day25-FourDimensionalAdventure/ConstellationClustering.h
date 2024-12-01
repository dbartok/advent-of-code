#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>
#include <Eigen/StdVector>

#include <list>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day25
{

using CoordinateType = int;
using Vector4D = Eigen::Matrix<CoordinateType, 4, 1>;
using Points = std::vector<Vector4D, Eigen::aligned_allocator<Vector4D>>;

class ConstellationClustering
{
public:
    ConstellationClustering(Points points);

    void formClusters();

    unsigned getNumClusters() const;

private:
    static const CoordinateType CONNECTED_CLUSTER_DISTANCE = 3;

    Points m_points;
    std::list<Points> m_clusters;

    void addPointToClustering(Vector4D point);

    static bool isPointConnectedWithCluster(const Vector4D& point, const Points& cluster);
};

}
}
}
