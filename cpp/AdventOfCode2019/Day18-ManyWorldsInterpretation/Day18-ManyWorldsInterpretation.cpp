#include "Day18-ManyWorldsInterpretation.h"

#include "VaultTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day18
{

void writeNewStartingPositions(VaultMap& vaultMap, int midX, int midY)
{
    vaultMap[midY][midX] = '#';
    vaultMap[midY - 1][midX] = '#';
    vaultMap[midY + 1][midX] = '#';
    vaultMap[midY][midX - 1] = '#';
    vaultMap[midY][midX + 1] = '#';
    vaultMap[midY - 1][midX - 1] = '@';
    vaultMap[midY + 1][midX - 1] = '@';
    vaultMap[midY - 1][midX + 1] = '@';
    vaultMap[midY + 1][midX + 1] = '@';
}

VaultMap getSubMap(const VaultMap& vaultMap, int minX, int minY, int maxX, int maxY)
{
    VaultMap subMap;

    for (int j = minY; j < maxY; ++j)
    {
        subMap.emplace_back();
        for (int i = minX; i < maxX; ++i)
        {
            subMap.back().push_back(vaultMap.at(j).at(i));
        }
    }

    return subMap;
}

std::vector<VaultMap> splitIntoFourQuadrants(VaultMap vaultMap)
{
    int midX = vaultMap.front().size() / 2;
    int midY = vaultMap.size() / 2;

    writeNewStartingPositions(vaultMap, midX, midY);

    int maxX = vaultMap.front().size();
    int maxY = vaultMap.size();

    VaultMap upperLeft = getSubMap(vaultMap, 0, 0, midX + 1, midY + 1);
    VaultMap upperRight = getSubMap(vaultMap, midX, 0, maxX, midY + 1);
    VaultMap lowerLeft = getSubMap(vaultMap, 0, midY, midX + 1, maxY);
    VaultMap lowerRight = getSubMap(vaultMap, midX, midY, maxX, maxY);

    return std::vector<VaultMap>{upperLeft, upperRight, lowerLeft, lowerRight};
}

int lengthOfShortestPathWithAllKeys(const std::vector<std::string>& vaultLines)
{
    VaultTraverser traverser{vaultLines};

    traverser.traverseAllKeys();

    return traverser.getShortestPathLength();
}

int lengthOfShortestPathWithAllKeysMultipleRobots(const std::vector<std::string>& vaultLines)
{
    std::vector<VaultMap> quadrants = splitIntoFourQuadrants(vaultLines);

    int totalLength = 0;

    for (const auto& quadrant : quadrants)
    {
        VaultTraverser traverser{quadrant};
        traverser.traverseAllKeys();

        totalLength += traverser.getShortestPathLength();
    }

    return totalLength;
}

}
}
}
