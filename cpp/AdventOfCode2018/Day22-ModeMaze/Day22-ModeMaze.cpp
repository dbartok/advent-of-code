#include "Day22-ModeMaze.h"

#include "CaveMap.h"
#include "CaveTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day22
{

CaveMap parseCaveMap(const std::vector<std::string>& depthAndTargetLines)
{
    std::vector<std::string> tokens;
    boost::split(tokens, depthAndTargetLines.at(0), boost::is_any_of(" "));
    unsigned depth = boost::lexical_cast<unsigned>(tokens.at(1));

    boost::split(tokens, depthAndTargetLines.at(1), boost::is_any_of(" ,"));
    unsigned targetX = boost::lexical_cast<unsigned>(tokens.at(1));
    unsigned targetY = boost::lexical_cast<unsigned>(tokens.at(2));

    return CaveMap{depth, Coordinates{targetY, targetX}};
}

unsigned riskLevelOfSmallestArea(const std::vector<std::string>& depthAndTargetLines)
{
    CaveMap caveMap = parseCaveMap(depthAndTargetLines);

    return caveMap.calculateRiskLevelOfArea();
}

unsigned fewestMinutesToTarget(const std::vector<std::string>& depthAndTargetLines)
{
    CaveMap caveMap = parseCaveMap(depthAndTargetLines);

    CaveTraverser caveTraverser{caveMap};
    caveTraverser.traverse();

    return caveTraverser.getLowestCostToTarget();
}

}
}
}
