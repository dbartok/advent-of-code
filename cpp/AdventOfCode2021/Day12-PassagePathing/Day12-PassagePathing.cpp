#include "Day12-PassagePathing.h"

#include "CaveTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day12
{

CaveConnection parseCaveConnectionLine(const std::string& caveConnectionLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, caveConnectionLine, boost::is_any_of("-"));

    return CaveConnection{std::move(tokens.at(0)), std::move(tokens.at(1))};
}

std::vector<CaveConnection> parseCaveConnectionLines(const std::vector<std::string>& caveConnectionLines)
{
    std::vector<CaveConnection> caveConnections;

    for (const auto& line : caveConnectionLines)
    {
        CaveConnection caveConnection = parseCaveConnectionLine(line);
        caveConnections.push_back(std::move(caveConnection));
    }

    return caveConnections;
}

unsigned numPathsWithSmallCavesVisitedAtMostOnce(const std::vector<std::string>& caveConnectionLines)
{
    std::vector<CaveConnection> caveConnections = parseCaveConnectionLines(caveConnectionLines);
    CaveTraverserWithSingleVisitationLimitLowercase caveTraverser{std::move(caveConnections)};
    caveTraverser.traverse();
    return caveTraverser.getNumPathsFromStartToEnd();
}

unsigned numPathsWithSmallCavesVisitedAtMostTwice(const std::vector<std::string>& caveConnectionLines)
{
    std::vector<CaveConnection> caveConnections = parseCaveConnectionLines(caveConnectionLines);
    CaveTraverserWithDoubleVisitationLimitForOneLowercase caveTraverser{std::move(caveConnections)};
    caveTraverser.traverse();
    return caveTraverser.getNumPathsFromStartToEnd();
}

}
}
}