#include "Day17-ReservoirResearch.h"

#include "WaterFlowSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day17
{

struct Range
{
    int begin;
    int end;

    Range(int begin, int end)
        : begin(begin)
        , end(end)
    {

    }

    Range(int begin)
        : Range(begin, begin)
    {

    }
};

Range parseRangeWithPrefix(const std::string& line, const std::string& prefix)
{
    std::regex rangeRegex(prefix + "([0-9]+(\\.\\.[0-9]+)?)");
    std::smatch matchResults;
    regex_search(line, matchResults, rangeRegex);

    if (matchResults.size() < 2)
    {
        throw std::runtime_error("Could not find range.");
    }

    std::string match = matchResults[1].str();

    std::vector<std::string> tokens;
    boost::split(tokens, match, boost::is_any_of("."), boost::token_compress_on);

    if (tokens.size() == 1)
    {
        return Range{std::stoi(tokens[0])};
    }
    else if (tokens.size() == 2)
    {
        return Range{std::stoi(tokens[0]), std::stoi(tokens[1])};
    }
    else
    {
        throw std::runtime_error("Invalid range specified.");
    }
}


CoordinatesToTile parseClayCoordinates(const std::vector<std::string>& clayCoordinatesLines)
{
    CoordinatesToTile clayCoordinates;

    for (const auto& line : clayCoordinatesLines)
    {
        Range xRange = parseRangeWithPrefix(line, "x=");
        Range yRange = parseRangeWithPrefix(line, "y=");

        for (int j = yRange.begin; j <= yRange.end; ++j)
        {
            for (int i = xRange.begin; i <= xRange.end; ++i)
            {
                clayCoordinates.emplace(Coordinates{j, i}, Tile::CLAY);
            }
        }
    }

    return clayCoordinates;
}

unsigned numTilesWaterCanReach(const std::vector<std::string>& clayCoordinatesLines)
{
    CoordinatesToTile clayCoordinates = parseClayCoordinates(clayCoordinatesLines);

    WaterFlowSimulator waterFlowSimulator{std::move(clayCoordinates)};
    waterFlowSimulator.run();

    return waterFlowSimulator.getNumTilesWithWater();
}

unsigned numTilesWaterRetained(const std::vector<std::string>& clayCoordinatesLines)
{
    CoordinatesToTile clayCoordinates = parseClayCoordinates(clayCoordinatesLines);

    WaterFlowSimulator waterFlowSimulator{std::move(clayCoordinates)};
    waterFlowSimulator.run();

    return waterFlowSimulator.getNumTilesWithSettledWater();
}

}
}
}
