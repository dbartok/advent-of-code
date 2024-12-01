#include "Day18-SettlersNorthPole.h"

#include "LumberLandscapeSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const unsigned NUM_CYCLES_SHORT = 10;
const unsigned NUM_CYCLES_LONG = 1'000'000'000;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day18
{

Acre parseAcre(char acreChar)
{
    if (acreChar == '|')
    {
        return Acre::TREE;
    }
    else if (acreChar == '.')
    {
        return Acre::OPEN;
    }
    else if (acreChar == '#')
    {
        return Acre::LUMBERYARD;
    }
    else
    {
        throw std::runtime_error("Unknown acre character: " + std::string{acreChar});
    }
}

LumberAreaRow parseLumberAreaRow(const std::string& lumberAreaLine)
{
    LumberAreaRow lumberAreaRow;

    for (const auto& c : lumberAreaLine)
    {
        lumberAreaRow.push_back(parseAcre(c));
    }

    return lumberAreaRow;
}

LumberArea parseLumberArea(const std::vector<std::string>& lumberAreaLines)
{
    LumberArea lumberArea;

    for (const auto& line : lumberAreaLines)
    {
        lumberArea.push_back(parseLumberAreaRow(line));
    }

    return lumberArea;
}

unsigned totalResourceValueAfterShortTime(const std::vector<std::string>& lumberAreaLines)
{
    LumberArea initialArea = parseLumberArea(lumberAreaLines);

    LumberLandscapeSimulator lumberLandscapeSimulator{std::move(initialArea)};
    lumberLandscapeSimulator.run(NUM_CYCLES_SHORT);

    return lumberLandscapeSimulator.getResourceValue();
}

unsigned totalResourceValueAfterLongTime(const std::vector<std::string>& lumberAreaLines)
{
    LumberArea initialArea = parseLumberArea(lumberAreaLines);

    LumberLandscapeSimulator lumberLandscapeSimulator{std::move(initialArea)};
    lumberLandscapeSimulator.run(NUM_CYCLES_LONG);

    return lumberLandscapeSimulator.getResourceValue();
}

}
}
}
