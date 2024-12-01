#include "Day17-ClumsyCrucible.h"

#include "CityBlockTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day17
{

std::vector<std::vector<int>> parseMapLines(const std::vector<std::string>& mapLines)
{
    std::vector<std::vector<int>> map(mapLines.size(), std::vector<int>(mapLines.front().size()));

    for (int j = 0; j < mapLines.size(); ++j)
    {
        for (int i = 0; i < mapLines.front().size(); ++i)
        {
            map.at(j).at(i) = mapLines.at(j).at(i) - '0';
        }
    }

    return map;
}

int leastHeatLossIncurred(const std::vector<std::string>& mapLines)
{
    std::vector<std::vector<int>> map = parseMapLines(mapLines);

    CityBlockTraverser cityBlockTraverser{std::move(map), 1, 3};

    cityBlockTraverser.traverse();

    return cityBlockTraverser.getMinHeatLoss();
}

int leastHeatLossIncurredForUltraCrucible(const std::vector<std::string>& mapLines)
{
    std::vector<std::vector<int>> map = parseMapLines(mapLines);

    CityBlockTraverser cityBlockTraverser{std::move(map), 4, 10};

    cityBlockTraverser.traverse();

    return cityBlockTraverser.getMinHeatLoss();
}

}
}
}