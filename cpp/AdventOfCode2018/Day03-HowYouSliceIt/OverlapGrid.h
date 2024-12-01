#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day03
{

struct Rectangle;
using Rectangles = std::vector<Rectangle>;

struct Rectangle
{
    unsigned topLeftX;
    unsigned topLeftY;
    unsigned width;
    unsigned height;

    Rectangle(unsigned topLeftX, unsigned topLeftY, unsigned width, unsigned height) noexcept;
};

class OverlapGrid
{
public:
    OverlapGrid(size_t size);

    void addRectangle(Rectangle rectangle);

    unsigned getOverlapSize() const;
    unsigned getSingleNonOverlappingIndex() const;

private:
    using Grid = std::vector<std::vector<int>>;

    Grid m_grid;
    std::vector<Rectangle> m_rectangles;
};

}
}
}
