#include "Day17-TrickShot.h"

#include "ProbeLauncherSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day17
{

TargetArea parseTargetAreaString(const std::string& targetAreaString)
{
    std::regex coordinatesRegex(R"(target area: x=(-?[0-9]+)..(-?[0-9]+), y=(-?[0-9]+)..(-?[0-9]+))");
    std::smatch coordinatesMatch;

    std::regex_match(targetAreaString, coordinatesMatch, coordinatesRegex);

    const int lowerBoundX = std::stoi(coordinatesMatch[1].str());
    const int upperBoundX = std::stoi(coordinatesMatch[2].str());
    const int lowerBoundY = std::stoi(coordinatesMatch[3].str());
    const int upperBoundY = std::stoi(coordinatesMatch[4].str());

    return TargetArea{{lowerBoundX, lowerBoundY}, {upperBoundX, upperBoundY}};
}

int highestYPositionToHitTarget(const std::string& targetAreaString)
{
    TargetArea targetArea = parseTargetAreaString(targetAreaString);
    ProbeLauncherSimulator probeLauncherSimulator{std::move(targetArea)};
    return probeLauncherSimulator.getHighestPossibleYPosition();
}

unsigned numDistinctInitialVelocityValuesToHitTarget(const std::string& targetAreaString)
{
    TargetArea targetArea = parseTargetAreaString(targetAreaString);
    ProbeLauncherSimulator probeLauncherSimulator{std::move(targetArea)};
    return probeLauncherSimulator.getNumDistinctInitialVelocityValues();
}

}
}
}