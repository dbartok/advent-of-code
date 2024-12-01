#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/dense>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day13
{

using Matrix = Eigen::MatrixXi;

class MirrorFinder
{
public:
    MirrorFinder(Matrix matrix);

    void find();
    void findSmudged();

    int getNoteNumber() const;

private:
    using MatrixComparisonFunc = std::function<bool(const Matrix&, const Matrix&)>;

    Matrix m_matrix;

    int m_horizontalMirrorPositionSubsequentIndex = -1;
    int m_verticalMirrorPositionSubsequentIndex = -1;

    int findHorizontalMirrorPositionSubsequentIndex(const MatrixComparisonFunc& cmp) const;
    int findVerticalMirrorPositionSubsequentIndex(const MatrixComparisonFunc& cmp) const;
};

}
}
}
