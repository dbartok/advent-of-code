#include "DefragmenterGrid.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day14
{

DefragmenterGrid::DefragmenterGrid(DiskGrid diskGrid) noexcept
    : m_diskGrid{std::move(diskGrid)}
{

}

unsigned DefragmenterGrid::numSquaresUsed() const
{
    return std::accumulate(m_diskGrid.cbegin(), m_diskGrid.cend(), 0u, [](unsigned totalSum, const auto& row)
                           {
                               return totalSum + std::accumulate(row.cbegin(), row.cend(), 0u, [](unsigned rowSum, bool cell) noexcept
                                                                 {
                                                                     if (cell)
                                                                     {
                                                                         ++rowSum;
                                                                     }

                                                                     return rowSum;
                                                                 });
                           });
}

unsigned DefragmenterGrid::numRegionsOfAdjcacentSquares() const
{
    if (!isRectangle())
    {
        throw std::runtime_error("Only available if the grid is a rectangle.");
    }

    DiskGrid diskGridCopy{m_diskGrid};

    unsigned numRegions = 0;
    for (size_t j = 0; j < diskGridCopy.size(); ++j)
    {
        for (size_t i = 0; i < diskGridCopy.front().size(); ++i)
        {
            if (diskGridCopy[j][i])
            {
                ++numRegions;
                clearRegion(diskGridCopy, i, j);
            }
        }
    }

    return numRegions;
}

bool DefragmenterGrid::isRectangle() const
{
    return Utils::allElementsEqual(m_diskGrid.cbegin(), m_diskGrid.cend(), [](const auto& lhs, const auto& rhs) noexcept
                                   {
                                       return lhs.size() == rhs.size();
                                   });
}

void DefragmenterGrid::clearRegion(DiskGrid& diskGrid, size_t i, size_t j)
{
    if (!diskGrid[j][i])
    {
        return;
    }

    diskGrid[j][i] = false;

    if (i != 0)
    {
        clearRegion(diskGrid, i - 1, j);
    }

    if (j != 0)
    {
        clearRegion(diskGrid, i, j - 1);
    }

    if (i != diskGrid.front().size() - 1)
    {
        clearRegion(diskGrid, i + 1, j);
    }

    if (j != diskGrid.size() - 1)
    {
        clearRegion(diskGrid, i, j + 1);
    }
}

}
}
}
