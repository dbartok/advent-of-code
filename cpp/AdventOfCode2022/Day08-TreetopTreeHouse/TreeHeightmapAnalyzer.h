#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/dense>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day08
{

using MatrixRow = Eigen::RowVectorXi;
using Matrix = Eigen::MatrixXi;

class TreeHeightmapAnalyzer
{
public:
    TreeHeightmapAnalyzer(Matrix heightmapMatrix);

    int getNumTreesVisibleFromOutsideTheGrid() const;
    int getHighestPossibleScenicScore() const;

private:
    Matrix m_heightmapMatrix;

    bool isTreeVisibleFromOutsideTheGrid(int x, int y) const;
    std::vector<MatrixRow> getSightlinesFrom(int x, int y) const;
    int getScenicScoreAt(int x, int y) const;
};

}
}
}
