#include "SmallSquare.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day21
{

SmallSquare::SmallSquare(DynamicBoolMatrix squareData)
    : m_squareData(squareData)
{

}

void SmallSquare::rotate()
{
    m_squareData.transposeInPlace();
    m_squareData.rowwise().reverseInPlace();
}

void SmallSquare::flipHorizontally()
{
    m_squareData.rowwise().reverseInPlace();
}

void SmallSquare::flipVertically()
{
    m_squareData.colwise().reverseInPlace();
}

int SmallSquare::size() const
{
    return m_squareData.rows();
}

const DynamicBoolMatrix& SmallSquare::getMatrix() const noexcept
{
    return m_squareData;
}

}
}
}
