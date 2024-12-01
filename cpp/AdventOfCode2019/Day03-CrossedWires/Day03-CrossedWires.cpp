#include "Day03-CrossedWires.h"

#include "WirePlanter.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/lexical_cast.hpp>

#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day03
{

Direction parseDirection(char directionChar)
{
    switch (directionChar)
    {
        case 'U':
            return Direction::UP;
        case 'D':
            return Direction::DOWN;
        case 'L':
            return Direction::LEFT;
        case 'R':
            return Direction::RIGHT;
        default:
            throw std::runtime_error("Unknown direction: " + std::string{directionChar});
    }
}

WireSection parseWireSection(const std::string& wireLine)
{
    const char directionChar = wireLine.at(0);
    const Direction direction = parseDirection(directionChar);

    std::string lengthString = wireLine.substr(1);
    const unsigned length = boost::lexical_cast<unsigned>(lengthString);

    return WireSection{direction, length};
}

Wire parseWire(const std::string& wireLine)
{
    std::vector<std::string> wireSectionStrings;
    Utils::splitStringIntoTypedVector(wireLine, wireSectionStrings, ',');

    std::vector<WireSection> wireSections;

    for (const auto& wireSectionString : wireSectionStrings)
    {
        wireSections.push_back(parseWireSection(wireSectionString));
    }

    return Wire{wireSections};
}

std::vector<Wire> parseWires(const std::vector<std::string>& wireLines)
{
    std::vector<Wire> wires;

    for (const auto& wireLine : wireLines)
    {
        wires.push_back(parseWire(wireLine));
    }

    return wires;
}


int distanceToClosestIntersection(const std::vector<std::string>& wireLines)
{
    std::vector<Wire> wires = parseWires(wireLines);

    WirePlanter wp{wires};

    wp.plant();

    return wp.getDistanceToClosestIntersection();
}

int combinedWireStepsToClosestIntersection(const std::vector<std::string>& wireLines)
{
    std::vector<Wire> wires = parseWires(wireLines);

    WirePlanter wp{wires};

    wp.plant();

    return wp.getCombinedWireStepsToClosestIntersection();
}

}
}
}
