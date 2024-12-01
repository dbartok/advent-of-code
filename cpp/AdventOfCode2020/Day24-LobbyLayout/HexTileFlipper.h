#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>
#include <boost/functional/hash.hpp>

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day24
{

using Vector2D = Eigen::Matrix<int, 2, 1>;

struct Vector2DHash
{
    size_t operator()(const Vector2D& vec) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, vec.x());
        boost::hash_combine(seed, vec.y());

        return seed;
    }
};

// Coordinates are defined as following:
// (x-asis points towards east, y-axis  points towards southeast)
//
//           +     +
//          / \   / \
//         /   \ /   \
//        +     +     +
//        |0, -1|1, -1|
//        +     +     +
//       / \   / \   / \
//      /   \ /   \ /   \
//     +     +     +     +
//     |-1, 0|0, 0 |1, 0 |
//     +     +     +     +
//      \   / \   / \   /
//       \ /   \ /   \ /
//        +     +     +
//        |-1, 1|0, 1 |
//        +     +     +
//         \   / \   /
//          \ /   \ /
//           +     +
//
class HexTileFlipper
{
public:
    HexTileFlipper(std::vector<std::string> tilePaths);

    void setupInitialState();
    void simulateMultipleDays(unsigned numDaysToSimulate);

    int getNumBlackTiles() const;

private:
    std::vector<std::string> m_tilePaths;
    std::unordered_set<Vector2D, Vector2DHash> m_blackTileCoordinatesSet;

    std::unordered_map<std::string, Vector2D> m_directionToUnitVector;

    void flipTileAtPath(const std::string& tilePath);
    void flipTileAtCoordinates(const Vector2D& coordinates);
    void simulateSingleDay();

    Vector2D getTileCoordinatesForPath(const std::string& tilePath) const;
    std::unordered_set<Vector2D, Vector2DHash> getAllRelevantCoordinatesForNextRound() const;
    bool isTileBlackInNextRound(const Vector2D& coordinates) const;
    std::vector<Vector2D> getAllAdjacentTileCoordinates(const Vector2D& coordinates) const;
    int getNumAdjacentBlackTiles(const Vector2D& coordinates) const;
};

}
}
}
