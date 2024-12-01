#include "TreeHeightmapAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day08
{

TreeHeightmapAnalyzer::TreeHeightmapAnalyzer(Matrix heightmapMatrix)
    : m_heightmapMatrix{std::move(heightmapMatrix)}
{

}

int TreeHeightmapAnalyzer::getNumTreesVisibleFromOutsideTheGrid() const
{
    int numTreesVisibleFromOutsideTheGrid = 0;

    for (int j = 0; j < m_heightmapMatrix.rows(); ++j)
    {
        for (int i = 0; i < m_heightmapMatrix.cols(); ++i)
        {
            if (isTreeVisibleFromOutsideTheGrid(i, j))
            {
                ++numTreesVisibleFromOutsideTheGrid;
            }
        }
    }

    return numTreesVisibleFromOutsideTheGrid;
}

int TreeHeightmapAnalyzer::getHighestPossibleScenicScore() const
{
    int maxScenicSore = 0;

    for (int j = 0; j < m_heightmapMatrix.rows(); ++j)
    {
        for (int i = 0; i < m_heightmapMatrix.cols(); ++i)
        {
            const int scenicScore = getScenicScoreAt(i, j);
            maxScenicSore = std::max(scenicScore, maxScenicSore);
        }
    }

    return maxScenicSore;
}

bool TreeHeightmapAnalyzer::isTreeVisibleFromOutsideTheGrid(int x, int y) const
{
    const int heightAtTreePosition = m_heightmapMatrix(x, y);
    const std::vector<MatrixRow> sightlines = getSightlinesFrom(x, y);

    return std::any_of(sightlines.cbegin(), sightlines.cend(), [heightAtTreePosition](const auto& sightline)
                        {
                            return std::all_of(sightline.cbegin(), sightline.cend(), [heightAtTreePosition](const auto& sightlinePositionHeight)
                                                {
                                                    return heightAtTreePosition > sightlinePositionHeight;
                                                });
                        });
}

std::vector<MatrixRow> TreeHeightmapAnalyzer::getSightlinesFrom(int x, int y) const
{
    // Axes in the Eigen library are defined as following:
    //
    //        y
    //     ------->
    //    |
    //   x|
    //    |
    //    V

    MatrixRow sightlineLeft = m_heightmapMatrix(Eigen::seq(x, x), Eigen::seq(0, y - 1)).reshaped().reverse();
    MatrixRow sightlineRight = m_heightmapMatrix(Eigen::seq(x, x), Eigen::seq(y + 1, m_heightmapMatrix.cols() - 1)).reshaped();
    MatrixRow sightlineUp = m_heightmapMatrix(Eigen::seq(0, x - 1), Eigen::seq(y, y)).reshaped().reverse();
    MatrixRow sightlineDown = m_heightmapMatrix(Eigen::seq(x + 1, m_heightmapMatrix.rows() - 1), Eigen::seq(y, y)).reshaped();

    return {sightlineLeft, sightlineRight, sightlineUp, sightlineDown};
}

int TreeHeightmapAnalyzer::getScenicScoreAt(int x, int y) const
{
    const int heightAtTreePosition = m_heightmapMatrix(x, y);
    std::vector<MatrixRow> sightlines = getSightlinesFrom(x, y);

    return std::accumulate(sightlines.cbegin(), sightlines.cend(), 1, [heightAtTreePosition](auto acc, const auto& sightline)
                            {
                                const auto endOfVisibilityIter = std::find_if(sightline.cbegin(), sightline.cend(), [heightAtTreePosition](const auto& sightlinePositionHeight)
                                                                                {
                                                                                    return heightAtTreePosition <= sightlinePositionHeight;
                                                                                });

                                const int viewingDistance = endOfVisibilityIter == sightline.cend() ? sightline.size() : endOfVisibilityIter - sightline.cbegin() + 1;

                                return acc * viewingDistance;
                            });
}

}
}
}
