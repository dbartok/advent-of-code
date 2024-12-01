#include "Day10-TheStarsAlign.h"

#include "StarAligner.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day10
{

std::vector<Starlight> createMoons(const std::vector<std::string>& starlightLines)
{
    std::vector<Starlight> starlights;

    for (const auto& line : starlightLines)
    {
        std::regex coordinatesRegex(R"(position=<\s*(-?[0-9]+),\s*(-?[0-9]+)>\s*velocity=<\s*(-?[0-9]+),\s*(-?[0-9]+)>)");
        std::smatch coordinatesMatch;

        std::regex_match(line, coordinatesMatch, coordinatesRegex);

        CoordinateNumericType posX = std::stoi(coordinatesMatch[1].str());
        CoordinateNumericType posY = std::stoi(coordinatesMatch[2].str());
        CoordinateNumericType velocityX = std::stoi(coordinatesMatch[3].str());
        CoordinateNumericType velocityY = std::stoi(coordinatesMatch[4].str());

        starlights.emplace_back(Vector2D{posX, posY}, Vector2D{velocityX, velocityY});
    }

    return starlights;

}

std::string serializedMessageWhenAligned(const std::vector<std::string>& starlightLines)
{
    std::vector<Starlight> starlights = createMoons(starlightLines);

    StarAligner starAligner{std::move(starlights)};
    starAligner.align();

    return starAligner.getSerializedMessage();
}

unsigned timeTakenUntilAligned(const std::vector<std::string>& starlightLines)
{
    std::vector<Starlight> starlights = createMoons(starlightLines);

    StarAligner starAligner{std::move(starlights)};
    starAligner.align();

    return starAligner.getTimeUnitsElapsed();
}

}
}
}
