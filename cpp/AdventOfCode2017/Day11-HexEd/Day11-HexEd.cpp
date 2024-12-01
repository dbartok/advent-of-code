#include "Day11-HexEd.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <cassert>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day11
{
// Coordinates are defined as following:
//
//      -----+ (0, -2) +-----
//            \   n   /
// (-1, -1) nw +-----+ ne (1, -1)
//            /       \
//      -----+  0, 0   +-----
//            \       /
//  (-1, 1) sw +-----+ se (1, 1)
//            /   s   \
//      -----+ (0, 2)  +-----

void applyStep(const std::string& step, std::pair<int, int>& coordinates)
{
    if (step == "n")
    {
        coordinates.second -= 2;
    }
    else if (step == "s")
    {
        coordinates.second += 2;
    }
    else if (step == "nw")
    {
        --coordinates.first;
        --coordinates.second;
    }
    else if (step == "sw")
    {
        --coordinates.first;
        ++coordinates.second;
    }
    else if (step == "ne")
    {
        ++coordinates.first;
        --coordinates.second;
    }
    else if (step == "se")
    {
        ++coordinates.first;
        ++coordinates.second;
    }
    else
    {
        throw std::runtime_error("Unknown step direction in path.");
    }

    assert((coordinates.first + coordinates.second) % 2 == 0);
}

int distanceFromStart(std::pair<int, int> coordinates) noexcept
{
    // We can calculate the distance as if the coordinates were in the bottom right quadrant
    coordinates.first = std::abs(coordinates.first);
    coordinates.second = std::abs(coordinates.second);

    // Calculate diagonal distance component
    int diagonalComponentLength = std::min(coordinates.first, coordinates.second);

    // After subtracting the diagonal component, either only a vertical or only the horizontal can remain, but never both
    coordinates.first -= diagonalComponentLength;
    coordinates.second -= diagonalComponentLength;

    int nonDiagonalComponentLength = 0;
    if (coordinates.first == 0) // Only vertical component remains
    {
        assert(coordinates.second % 2 == 0);
        nonDiagonalComponentLength = coordinates.second / 2;
    }
    else if (coordinates.second == 0) // Only horizontal component remains
    {
        assert(coordinates.first % 2 == 0);
        nonDiagonalComponentLength = coordinates.first;
    }
    else
    {
        assert(false);
    }

    return diagonalComponentLength + nonDiagonalComponentLength;
}

int numStepsFromStartAtEnd(const std::vector<std::string>& path)
{
    std::pair<int, int> coordinates{0, 0};

    for (const auto& step : path)
    {
        applyStep(step, coordinates);
    }

    return distanceFromStart(coordinates);
}

int maxNumStepsFromStart(const std::vector<std::string>& path)
{
    std::pair<int, int> coordinates{0, 0};
    int maxDistance = std::numeric_limits<int>::min();

    for (const auto& step : path)
    {
        applyStep(step, coordinates);
        maxDistance = std::max(maxDistance, distanceFromStart(coordinates));
    }

    return maxDistance;
}

}
}
}
