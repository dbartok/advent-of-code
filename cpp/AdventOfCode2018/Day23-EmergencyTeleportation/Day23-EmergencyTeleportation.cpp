#include "Day23-EmergencyTeleportation.h"

#include "NanobotsAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day23
{

std::vector<Nanobot> parseNanobots(const std::vector<std::string>& nanobotLines)
{
    std::vector<Nanobot> nanobots;

    for (const auto& line : nanobotLines)
    {
        std::regex nanobotLineRegex(R"(pos=<(-?[0-9]+),(-?[0-9]+),(-?[0-9]+)>,\s*r=(-?[0-9]+))");
        std::smatch nanobotLineMatch;

        std::regex_match(line, nanobotLineMatch, nanobotLineRegex);

        CoordinateType posX = std::stoi(nanobotLineMatch[1].str());
        CoordinateType posY = std::stoi(nanobotLineMatch[2].str());
        CoordinateType posZ = std::stoi(nanobotLineMatch[3].str());
        CoordinateType range = std::stoi(nanobotLineMatch[4].str());

        nanobots.emplace_back(Vector3D{posX, posY, posZ}, range);
    }

    return nanobots;
}

unsigned numNanobotsInStrongestRange(const std::vector<std::string>& nanobotLines)
{
    std::vector<Nanobot> nanobots = parseNanobots(nanobotLines);

    NanobotsAnalyzer nanobotsAnalyzer{nanobots};

    return nanobotsAnalyzer.numNanobotsInStrongestRange();
}

int lowestDistanceFromOriginWithMostNanobots(const std::vector<std::string>& nanobotLines)
{
    std::vector<Nanobot> nanobots = parseNanobots(nanobotLines);

    NanobotsAnalyzer nanobotsAnalyzer{nanobots};

    return nanobotsAnalyzer.lowestDistanceFromOriginWithMostNanobots();
}

}
}
}
