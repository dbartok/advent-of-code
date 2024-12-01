#include "Day11-CosmicExpansion.h"

#include "GalaxyImageAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day11
{

int64_t sumOfShortestPathsBetweenAllPairs(const std::vector<std::string>& imageLines)
{
    GalaxyImageAnalyzer galaxyImageAnalyzer{imageLines};

    galaxyImageAnalyzer.analyze();

    return galaxyImageAnalyzer.getSumOfAllShortestPathsBetweenAllPairs();
}

int64_t sumOfShortestPathsBetweenAllPairsWithLargerExpansionRate(const std::vector<std::string>& imageLines, int expansionRate)
{
    GalaxyImageAnalyzer galaxyImageAnalyzer{imageLines, expansionRate};

    galaxyImageAnalyzer.analyze();

    return galaxyImageAnalyzer.getSumOfAllShortestPathsBetweenAllPairs();
}

}
}
}