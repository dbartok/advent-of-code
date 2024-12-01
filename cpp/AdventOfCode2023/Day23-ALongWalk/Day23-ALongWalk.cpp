#include "Day23-ALongWalk.h"

#include "ForestTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS

__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day23
{

std::vector<std::string> getMapWithSlopesRemoved(std::vector<std::string> map)
{
    for (size_t j = 0; j < map.size(); ++j)
    {
        for (size_t i = 0; i < map.front().size(); ++i)
        {
            if (map.at(j).at(i) != FOREST)
            {
                map.at(j).at(i) = PATH;
            }
        }
    }

    return map;
}

int numStepsInLongestHike(const std::vector<std::string>& forestMapLines)
{
    ForestTraverser forestTraverser{forestMapLines};

    forestTraverser.traverse();

    return forestTraverser.getLongestPathLength();
}

int numStepsInLongestHikeWithoutSlopes(const std::vector<std::string>& forestMapLines)
{
    const std::vector<std::string> mapWithSlopesRemoved = getMapWithSlopesRemoved(forestMapLines);

    ForestTraverser forestTraverser{mapWithSlopesRemoved};

    forestTraverser.traverse();

    return forestTraverser.getLongestPathLength();
}

}
}
}