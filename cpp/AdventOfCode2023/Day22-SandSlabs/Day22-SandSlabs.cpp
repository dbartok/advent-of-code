#include "Day22-SandSlabs.h"

#include "BrickFallingSimulator.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day22
{

Vector3D parsePositionString(const std::string& positionString)
{
    std::vector<int> coordinates;
    AdventOfCode::Utils::splitStringIntoTypedVector(positionString, coordinates, ',');

    return Vector3D{coordinates.data()};
}

Brick parseBrickSnapshotLine(const std::string& brickSnapshotLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, brickSnapshotLine, boost::is_any_of("~"));

    Vector3D startPosition = parsePositionString(tokens.front());
    Vector3D endPosition = parsePositionString(tokens.back());

    return Brick{std::move(startPosition), std::move(endPosition)};
}

std::vector<Brick> parseBrickSnapshotLines(const std::vector<std::string>& brickSnapshotLines)
{
    std::vector<Brick> bricks;

    for (const auto& line : brickSnapshotLines)
    {
        Brick brick = parseBrickSnapshotLine(line);
        bricks.push_back(std::move(brick));
    }

    return bricks;
}

std::vector<Brick> createCopyWithOneElementRemoved(const std::vector<Brick>& initiallySettledBricks, const Brick& brickToDisintegrate)
{
    std::vector<Brick> copyWithOneElementRemoved;

    for (const auto& brick : initiallySettledBricks)
    {
        if (brick != brickToDisintegrate)
        {
            copyWithOneElementRemoved.push_back(brick);
        }
    }

    return copyWithOneElementRemoved;
}

std::vector<int> getNumBricksFallingForAllDisintegrations(const std::vector<std::string>& brickSnapshotLines)
{
    std::vector<Brick> inputBricks = parseBrickSnapshotLines(brickSnapshotLines);
    BrickFallingSimulator brickFallingSimulator{std::move(inputBricks)};

    brickFallingSimulator.settle();

    std::vector<Brick> initiallySettledBricks = brickFallingSimulator.getBricks();

    std::vector<int> numBricksFallingForAllDisintegrations;

    for (const auto& brickToDisintegrate : initiallySettledBricks)
    {
        std::vector<Brick> bricksWithOneBrickDisintegrated = createCopyWithOneElementRemoved(initiallySettledBricks, brickToDisintegrate);
        BrickFallingSimulator brickFallingSimulator{std::move(bricksWithOneBrickDisintegrated)};
        int numBricksMoved = brickFallingSimulator.settle();
        numBricksFallingForAllDisintegrations.push_back(numBricksMoved);
    }

    return numBricksFallingForAllDisintegrations;
}

int numBricksSafeToDisintegrate(const std::vector<std::string>& brickSnapshotLines)
{
    std::vector<int> numBricksFallingForAllDisintegrations = getNumBricksFallingForAllDisintegrations(brickSnapshotLines);

    return std::count(numBricksFallingForAllDisintegrations.cbegin(), numBricksFallingForAllDisintegrations.cend(), 0);
}

int sumOfNumBricksFallingAcrossAllDisintegrations(const std::vector<std::string>& brickSnapshotLines)
{
    std::vector<int> numBricksFallingForAllDisintegrations = getNumBricksFallingForAllDisintegrations(brickSnapshotLines);

    return std::accumulate(numBricksFallingForAllDisintegrations.cbegin(), numBricksFallingForAllDisintegrations.cend(), 0);
}

}
}
}