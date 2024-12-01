#include "Day25-FourDimensionalAdventure.h"

#include "ConstellationClustering.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day25
{

Points parsePoints(const std::vector<std::string>& pointsLines)
{
    Points points;

    std::regex coordinatesRegex(R"((-?[0-9]+),(-?[0-9]+),(-?[0-9]+),(-?[0-9]+))");

    for (const auto& line : pointsLines)
    {
        std::smatch coordinatesMatch;
        std::regex_match(line, coordinatesMatch, coordinatesRegex);

        CoordinateType x = std::stoi(coordinatesMatch[1].str());
        CoordinateType y = std::stoi(coordinatesMatch[2].str());
        CoordinateType z = std::stoi(coordinatesMatch[3].str());
        CoordinateType t = std::stoi(coordinatesMatch[4].str());

        points.emplace_back(x, y, z, t);
    }

    return points;
}

unsigned numConstellationsFormed(const std::vector<std::string>& pointsLines)
{
    Points points = parsePoints(pointsLines);

    ConstellationClustering constellationClustering{points};
    constellationClustering.formClusters();

    return constellationClustering.getNumClusters();
}

}
}
}
