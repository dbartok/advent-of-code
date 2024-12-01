#include "Day14-RegolithReservoir.h"

#include "SandFlowSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int FLOOR_OFFSET = 2;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day14
{

std::vector<Coordinates> getAllCoordinatesDescribingPath(const std::string& rockPathLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, rockPathLine, boost::is_any_of(" ->,"), boost::token_compress_on);

    std::vector<Coordinates> allCoordinatesDescribingPath;

    for (size_t i = 0; i < tokens.size(); i += 2)
    {
        allCoordinatesDescribingPath.emplace_back(std::stoi(tokens.at(i)), std::stoi(tokens.at(i + 1)));
    }

    return allCoordinatesDescribingPath;
}

int getStep(int from, int to)
{
    if (from == to)
    {
        return 0;
    }

    return (to - from) / std::abs(to - from);
}

CoordinatesSet getAllRockCoordinatesInPathSection(const Coordinates& fromCoordinates, const Coordinates& toCoordinates)
{
    CoordinatesSet allRockCoordinatesInPathSection;

    const int deltaX = getStep(fromCoordinates.first, toCoordinates.first);
    const int deltaY = getStep(fromCoordinates.second, toCoordinates.second);

    for (Coordinates c = fromCoordinates; c != toCoordinates; c.first += deltaX, c.second += deltaY)
    {
        allRockCoordinatesInPathSection.insert(c);
    }

    allRockCoordinatesInPathSection.insert(toCoordinates);

    return allRockCoordinatesInPathSection;
}

CoordinatesSet getAllRockCoordinatesInPath(const std::vector<Coordinates>& rockPath)
{
    CoordinatesSet allRockCoordinatesInPath;

    for (auto coordinatesIter = rockPath.cbegin(); coordinatesIter < rockPath.cend() - 1; ++coordinatesIter)
    {
        const auto& fromCoordinates = *coordinatesIter;
        const auto& toCoordinates = *std::next(coordinatesIter);

        CoordinatesSet allRockCoordinatesInPathSection = getAllRockCoordinatesInPathSection(fromCoordinates, toCoordinates);
        allRockCoordinatesInPath.insert(std::make_move_iterator(allRockCoordinatesInPathSection.begin()), std::make_move_iterator(allRockCoordinatesInPathSection.end()));
    }

    return allRockCoordinatesInPath;
}

CoordinatesSet parseRockPathLine(const std::string& rockPathLine)
{
    std::vector<Coordinates> rockPath = getAllCoordinatesDescribingPath(rockPathLine);
    return getAllRockCoordinatesInPath(rockPath);
}

CoordinatesSet parseRockPathLines(const std::vector<std::string>& rockPathLines)
{
    CoordinatesSet allRockCoordinatesInPaths;

    for (const auto& rockPathLine : rockPathLines)
    {
        CoordinatesSet allRockCoordinatesInSinglePath = parseRockPathLine(rockPathLine);
        allRockCoordinatesInPaths.insert(std::make_move_iterator(allRockCoordinatesInSinglePath.begin()), std::make_move_iterator(allRockCoordinatesInSinglePath.end()));
    }

    return allRockCoordinatesInPaths;
}

void addFloor(CoordinatesSet& allRockCoordinates)
{
    const auto elementWithMaxYCoordinateIter = std::max_element(allRockCoordinates.cbegin(), allRockCoordinates.cend(), [](const auto& lhs, const auto& rhs)
                                                          {
                                                              return lhs.second < rhs.second;
                                                          });
    const int maxY = elementWithMaxYCoordinateIter->second;
    const int floorY = maxY + FLOOR_OFFSET;

    for (int x = -SIMULATION_BOUNDARY_COORDINATE; x <= SIMULATION_BOUNDARY_COORDINATE; ++x)
    {
        allRockCoordinates.emplace(x, floorY);
    }
}

unsigned numSettledUnitsBeforeSandFlowsIntoAbyss(const std::vector<std::string>& rockPathLines)
{
    CoordinatesSet allRockCoordinates = parseRockPathLines(rockPathLines);

    SandFlowSimulator sandFlowSimulator{std::move(allRockCoordinates)};

    sandFlowSimulator.simulate();

    return sandFlowSimulator.getNumSettledUnits();
}

unsigned numSettledUnitsWithFloor(const std::vector<std::string>& rockPathLines)
{
    CoordinatesSet allRockCoordinates = parseRockPathLines(rockPathLines);
    addFloor(allRockCoordinates);

    SandFlowSimulator sandFlowSimulator{std::move(allRockCoordinates)};

    sandFlowSimulator.simulate();

    return sandFlowSimulator.getNumSettledUnits();
}

}
}
}