#include "SlopeChecker.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char TREE = '#';

}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day03
{

SlopeChecker::SlopeChecker(TreeGrid treeGrid)
    : m_treeGrid{std::move(treeGrid)}
{

}

int64_t SlopeChecker::getNumTreesForSlope(const Vector2D& slope) const
{
    Vector2D currentCoords{0, 0};
    int64_t numTrees = 0;

    while (currentCoords[1] < m_treeGrid.size())
    {
        if (m_treeGrid.at(currentCoords[1]).at(currentCoords[0]) == TREE)
        {
            ++numTrees;
        }

        currentCoords += slope;
        currentCoords[0] %= m_treeGrid.at(0).size();
    }

    return numTrees;
}

}
}
}
