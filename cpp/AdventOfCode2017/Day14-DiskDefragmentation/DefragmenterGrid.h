#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <bitset>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day14
{

class DefragmenterGrid
{
public:
    using DiskGrid = std::vector<std::vector<bool>>;

    DefragmenterGrid(DiskGrid diskGrid) noexcept;
    unsigned numSquaresUsed() const;
    unsigned numRegionsOfAdjcacentSquares() const;

private:
    DiskGrid m_diskGrid;

    bool isRectangle() const;

    static void clearRegion(DiskGrid& diskGrid, size_t i, size_t j);
};

}
}
}
