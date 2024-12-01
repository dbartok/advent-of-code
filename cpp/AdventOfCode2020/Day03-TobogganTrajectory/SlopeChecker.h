#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>

#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day03
{

using Vector2D = Eigen::Matrix<int64_t, 2, 1>;
using TreeGrid = std::vector<std::string>;

class SlopeChecker
{
public:
    SlopeChecker(TreeGrid treeGrid);

    int64_t getNumTreesForSlope(const Vector2D& slope) const;

private:
    TreeGrid m_treeGrid;
};

}
}
}
