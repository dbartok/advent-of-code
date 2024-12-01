#include "Day12-DigitalPlumber.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day12
{

unsigned numNodesInGroupNodeZero(const std::vector<std::string>& neighborsLines)
{
    VillageGraph villageGraph = VillageGraph::fromNeighborsLines(neighborsLines);
    return villageGraph.numNodesInGroupContainingNode(0);
}

unsigned numTotalGroups(const std::vector<std::string>& neighborsLines)
{
    VillageGraph villageGraph = VillageGraph::fromNeighborsLines(neighborsLines);
    return villageGraph.numTotalGroups();
}

}
}
}
