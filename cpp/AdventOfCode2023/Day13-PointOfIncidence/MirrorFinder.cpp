#include "MirrorFinder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int HORIZONTAL_MIRROR_MULTIPLIER = 100;

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day13
{

MirrorFinder::MirrorFinder(Matrix matrix)
    : m_matrix{std::move(matrix)}
{

}

void MirrorFinder::find()
{
    const auto exactMatch = [](const Matrix& upperHalf, const Matrix& lowerHalf) { return upperHalf == lowerHalf; };
    m_horizontalMirrorPositionSubsequentIndex = findHorizontalMirrorPositionSubsequentIndex(exactMatch);
    m_verticalMirrorPositionSubsequentIndex = findVerticalMirrorPositionSubsequentIndex(exactMatch);
}

void MirrorFinder::findSmudged()
{
    const auto smudgedMatch = [](const Matrix& upperHalf, const Matrix& lowerHalf)
    {
        return (upperHalf - lowerHalf).cwiseAbs().sum() == 1;
    };
    m_horizontalMirrorPositionSubsequentIndex = findHorizontalMirrorPositionSubsequentIndex(smudgedMatch);
    m_verticalMirrorPositionSubsequentIndex = findVerticalMirrorPositionSubsequentIndex(smudgedMatch);
}

int MirrorFinder::getNoteNumber() const
{
    if (m_horizontalMirrorPositionSubsequentIndex != -1)
    {
        return m_horizontalMirrorPositionSubsequentIndex * HORIZONTAL_MIRROR_MULTIPLIER;
    }
    else if (m_verticalMirrorPositionSubsequentIndex != -1)
    {
        return m_verticalMirrorPositionSubsequentIndex;
    }
    else
    {
        throw std::runtime_error("No mirrors found");
    }
}

int MirrorFinder::findHorizontalMirrorPositionSubsequentIndex(const MatrixComparisonFunc& cmp) const
{
    for (int potentialMirrorPositionSubsequentIndex = 1; potentialMirrorPositionSubsequentIndex < m_matrix.rows(); ++potentialMirrorPositionSubsequentIndex)
    {
        const size_t mirroredHeight = potentialMirrorPositionSubsequentIndex <= m_matrix.rows() / 2 ? potentialMirrorPositionSubsequentIndex : m_matrix.rows() - potentialMirrorPositionSubsequentIndex;

        Matrix upperHalf = m_matrix.block(potentialMirrorPositionSubsequentIndex - mirroredHeight, 0, mirroredHeight, m_matrix.cols());
        Matrix lowerHalf = m_matrix.block(potentialMirrorPositionSubsequentIndex, 0, mirroredHeight, m_matrix.cols());

        lowerHalf.colwise().reverseInPlace();

        if (cmp(upperHalf, lowerHalf))
        {
            return potentialMirrorPositionSubsequentIndex;
        }
    }

    return -1;
}

int MirrorFinder::findVerticalMirrorPositionSubsequentIndex(const MatrixComparisonFunc& cmp) const
{
    auto* non_const_this = const_cast<MirrorFinder*>(this);

    non_const_this->m_matrix.transposeInPlace();

    const int verticalMirrorPositionSubsequentIndex = findHorizontalMirrorPositionSubsequentIndex(cmp);

    non_const_this->m_matrix.transposeInPlace();

    return verticalMirrorPositionSubsequentIndex;
}

}
}
}
