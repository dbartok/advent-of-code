#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>

#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day17
{
struct Coordinates;
enum class Tile;
struct CoordinatesHash;
using CoordinatesToTile = std::unordered_map<Coordinates, Tile, CoordinatesHash>;

enum class Tile
{
    SAND,
    CLAY,
    FLOWING_WATER,
    SETTLED_WATER,
};

struct Coordinates
{
    int x;
    int y;

    Coordinates(int y, int x)
        : x{x}
        , y{y}
    {

    }

    bool operator==(const Coordinates& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct CoordinatesHash
{
    std::size_t operator()(const Coordinates& coordinates) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, coordinates.x);
        boost::hash_combine(seed, coordinates.y);

        return seed;
    }
};

class WaterFlowSimulator
{
public:
    WaterFlowSimulator(CoordinatesToTile clayCoordinates);

    void run();

    unsigned getNumTilesWithWater() const;
    unsigned getNumTilesWithSettledWater() const;

private:
    const Coordinates SPRING_START_POS = {0, 500};

    CoordinatesToTile m_coordinatesToTile;
    int m_minY;
    int m_maxY;

    void startSpring(const Coordinates& springStartPos);

    void spreadHorizontallyAndUpwards(const Coordinates& spreadStartPos);
    void spreadHorizontally(const Coordinates& spreadStartPos);
    void fillUp(const Coordinates& leftWall, const Coordinates& rightWall, Tile tileValue);
    void startSpringIfFree(const Coordinates& springStartPos);

    Coordinates boundLeft(Coordinates coordinates);
    Coordinates boundRight(Coordinates coordinates);
    Coordinates iterateUntil(Coordinates coordinates, const std::function<void(Coordinates&)> iterFunc);

    Tile getTileAt(const Coordinates& coordinates) const;
    bool tileIsFreeAt(const Coordinates& coordinates) const;
    void setTileAt(const Coordinates& coordinates, Tile newValue);
};

}
}
}
