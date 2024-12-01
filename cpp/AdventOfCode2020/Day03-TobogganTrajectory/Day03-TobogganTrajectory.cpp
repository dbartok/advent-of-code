#include "Day03-TobogganTrajectory.h"

#include "SlopeChecker.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <array>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

using AdventOfCode::Year2020::Day03::Vector2D;

const Vector2D STANDARD_SLOPE{3, 1};
const std::array<Vector2D, 5> ALL_SLOPES{STANDARD_SLOPE, Vector2D{1, 1}, Vector2D{5, 1}, Vector2D{7, 1}, Vector2D{1, 2}};

}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day03
{

int64_t numTreesEncounteredSingleSlope(const std::vector<std::string>& gridLines)
{
    SlopeChecker slopeChecker{gridLines};
    return slopeChecker.getNumTreesForSlope(STANDARD_SLOPE);
}

int64_t numTreesEncounteredMultipleSlopes(const std::vector<std::string>& gridLines)
{
    SlopeChecker slopeChecker{gridLines};
    int64_t productOfNumTreesOnAllSlopes = 1;

    for (const auto& slope : ALL_SLOPES)
    {
        const int64_t currentNumTrees = slopeChecker.getNumTreesForSlope(slope);
        productOfNumTreesOnAllSlopes *= currentNumTrees;
    }

    return productOfNumTreesOnAllSlopes;
}

}
}
}
