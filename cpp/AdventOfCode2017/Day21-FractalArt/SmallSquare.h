#pragma once

#include "DynamicBoolMatrix.h"

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

class SmallSquare
{
public:
    SmallSquare(DynamicBoolMatrix squareData);

    void rotate();
    void flipHorizontally();
    void flipVertically();

    int size() const;
    const DynamicBoolMatrix& getMatrix() const noexcept;

    bool operator==(const SmallSquare& other) const
    {
        return this->m_squareData.rows() == other.m_squareData.rows() &&
            this->m_squareData.cols() == other.m_squareData.cols() &&
            this->m_squareData == other.m_squareData;
    }

private:
    DynamicBoolMatrix m_squareData;

};

}
}
}
