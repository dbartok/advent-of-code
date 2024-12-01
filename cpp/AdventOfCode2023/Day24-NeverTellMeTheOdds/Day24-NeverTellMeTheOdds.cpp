#include "Day24-NeverTellMeTheOdds.h"

#include "HailstoneSystem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day24
{

Hailstone parseHailStoneLine(const std::string& hailstoneLine)
{
    std::vector<std::string> tokens;

    boost::split(tokens, hailstoneLine, boost::is_any_of("@, "), boost::token_compress_on);

    Vector3D position{std::stod(tokens.at(0)), std::stod(tokens.at(1)), std::stod(tokens.at(2))};
    Vector3D velocity{std::stod(tokens.at(3)), std::stod(tokens.at(4)), std::stod(tokens.at(5))};

    return Hailstone{std::move(position), std::move(velocity)};
}

std::vector<Hailstone> parseHailStoneLines(const std::vector<std::string>& hailstoneLines)
{
    std::vector<Hailstone> hailstones;

    for (const auto& line : hailstoneLines)
    {
        Hailstone hailstone = parseHailStoneLine(line);
        hailstones.push_back(std::move(hailstone));
    }

    return hailstones;
}

int numXYIntersectionsWithinTestArea(const std::vector<std::string>& hailstoneLines, double testAreaMin, double testAreaMax)
{
    std::vector<Hailstone> hailstones = parseHailStoneLines(hailstoneLines);

    HailstoneSystem hailstoneSystem{std::move(hailstones)};

    return hailstoneSystem.getNumXYIntersectionsWithinTestArea(testAreaMin, testAreaMax);
}

int64_t sumOfCoordinatesOfIniitialRockPosition(const std::vector<std::string>& hailstoneLines)
{
    std::vector<Hailstone> hailstones = parseHailStoneLines(hailstoneLines);

    for (int xySum = 2; ; ++xySum)
    {
        for (int x = 1; x < xySum; ++x)
        {
            for (int minusOneMultiplierBits = 0; minusOneMultiplierBits < 4; ++minusOneMultiplierBits)
            {
                const int y = xySum - x;

                const int signedX = minusOneMultiplierBits % 2 == 1 ? x : -x;
                const int signedY = (minusOneMultiplierBits >> 1) % 2 == 1 ? y : -y;

                HailstoneSystem hailstoneSystem{hailstones};
                hailstoneSystem.calculateRockStartingPositionForRockVelocityXY({signedX, signedY, 0});

                boost::optional<Vector3D> rockStartingPosition = hailstoneSystem.getRockStartingPosition();

                if (rockStartingPosition)
                {
                    return rockStartingPosition.get().sum().convert_to<int64_t>();
                }
            }
        }
    }

    HailstoneSystem hailstoneSystem{std::move(hailstones)};

}

}
}
}