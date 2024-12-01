#include "OverlapGrid.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <algorithm>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day03
{

Rectangle::Rectangle(unsigned topLeftX, unsigned topLeftY, unsigned width, unsigned height) noexcept
    : topLeftX{topLeftX}
    , topLeftY{topLeftY}
    , width{width}
    , height{height}
{

}

OverlapGrid::OverlapGrid(size_t size)
    : m_grid(size, std::vector<int>(size, 0))
{

}

void OverlapGrid::addRectangle(Rectangle rectangle)
{
    m_rectangles.push_back(std::move(rectangle));

    for (unsigned i = rectangle.topLeftX; i < rectangle.topLeftX + rectangle.width; ++i)
    {
        for (unsigned j = rectangle.topLeftY; j < rectangle.topLeftY + rectangle.height; ++j)
        {
            ++m_grid[j][i];
        }
    }
}

unsigned OverlapGrid::getOverlapSize() const
{
    return std::accumulate(m_grid.cbegin(), m_grid.cend(), 0u, [](unsigned acc, const std::vector<int>& row)
                           {
                               return acc + std::count_if(row.cbegin(), row.cend(), [](int i) noexcept
                                                          {
                                                              return i >= 2;
                                                          });
                           });
}

unsigned OverlapGrid::getSingleNonOverlappingIndex() const
{
    size_t rectangleIndex = 0;
    for (const auto& rectangle : m_rectangles)
    {
        auto beginRowIter = m_grid.cbegin() + rectangle.topLeftY;
        auto endRowIter = beginRowIter + rectangle.height;
        bool isNoOverlap = std::all_of(beginRowIter, endRowIter, [&rectangle](const std::vector<int>& row)
                                       {
                                           auto beginElemIter = row.cbegin() + rectangle.topLeftX;
                                           auto endElemIter = beginElemIter + rectangle.width;
                                           return std::all_of(beginElemIter, endElemIter, [](int i) noexcept
                                                              {
                                                                  return i == 1;
                                                              });
                                       });

        if (isNoOverlap)
        {
            return rectangleIndex;
        }

        ++rectangleIndex;
    }

    throw std::runtime_error("No rectangle found without overlaps.");
}

}
}
}
