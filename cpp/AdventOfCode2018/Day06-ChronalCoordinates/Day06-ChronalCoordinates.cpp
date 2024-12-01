#include "Day06-ChronalCoordinates.h"

#include "GridAreaAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day06
{

std::vector<Coordinates> parseCoordinates(const std::vector<std::string>& coordinatesLines)
{
    std::vector<Coordinates> allCoordinates;

    for (const auto& lines : coordinatesLines)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, lines, boost::is_any_of(" ,"), boost::token_compress_on);

        unsigned x = boost::lexical_cast<unsigned>(tokens[0]);
        unsigned y = boost::lexical_cast<unsigned>(tokens[1]);

        allCoordinates.emplace_back(x, y);
    }

    return allCoordinates;
}

unsigned sizeOfLargestNonInfiniteArea(const std::vector<std::string>& coordinatesLines)
{
    std::vector<Coordinates> allCoordinates = parseCoordinates(coordinatesLines);

    GridAreaAnalyzer gridAnalyzer{std::move(allCoordinates)};

    return gridAnalyzer.getLargestNonInfiniteArea();
}

unsigned sizeOfAreaWithinGivenDistance(const std::vector<std::string>& coordinatesLines, unsigned distanceThreshold)
{
    std::vector<Coordinates> allCoordinates = parseCoordinates(coordinatesLines);

    GridAreaAnalyzer gridAnalyzer{std::move(allCoordinates)};

    return gridAnalyzer.getAreaWithinGivenDistance(distanceThreshold);
}

}
}
}
