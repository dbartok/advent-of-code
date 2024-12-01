#pragma once

#include "InfiniteGrid.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day03
{

template <typename T>
static T sumOfAllNeighbors(const InfiniteGrid<T>& grid, const std::pair<int, int>& position)
{
    T sum{};

    for (int i = position.first - 1; i <= position.first + 1; i++)
    {
        for (int j = position.second - 1; j <= position.second + 1; j++)
        {
            if (i == position.first && j == position.second)
            {
                continue;
            }

            sum += grid.getValue(i, j);
        }
    }

    return sum;
}

}
}
}
