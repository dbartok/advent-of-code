#include "ConstellationClustering.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day25
{

ConstellationClustering::ConstellationClustering(Points points)
    : m_points{std::move(points)}
{

}

void ConstellationClustering::formClusters()
{
    for (const auto& point : m_points)
    {
        addPointToClustering(point);
    }
}

unsigned ConstellationClustering::getNumClusters() const
{
    return m_clusters.size();
}

void ConstellationClustering::addPointToClustering(Vector4D point)
{
    Points newCluster;

    for (auto clusterIter = m_clusters.begin(); clusterIter != m_clusters.end(); )
    {
        if (isPointConnectedWithCluster(point, *clusterIter))
        {
            std::copy(std::make_move_iterator(clusterIter->begin()), std::make_move_iterator(clusterIter->end()), std::back_inserter(newCluster));
            clusterIter = m_clusters.erase(clusterIter);
        }
        else
        {
            ++clusterIter;
        }
    }

    newCluster.push_back(std::move(point));

    m_clusters.push_back(std::move(newCluster));
}

bool ConstellationClustering::isPointConnectedWithCluster(const Vector4D& point, const Points& cluster)
{
    for (const auto& clusterPoint : cluster)
    {
        Vector4D difference = clusterPoint - point;
        if (difference.cwiseAbs().sum() <= CONNECTED_CLUSTER_DISTANCE)
        {
            return true;
        }
    }

    return false;
}

}
}
}
