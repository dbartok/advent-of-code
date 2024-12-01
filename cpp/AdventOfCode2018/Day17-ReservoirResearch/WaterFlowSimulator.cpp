#include "WaterFlowSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day17
{
WaterFlowSimulator::WaterFlowSimulator(CoordinatesToTile clayCoordinates)
    : m_coordinatesToTile{std::move(clayCoordinates)}
{
    auto minmaxIters = std::minmax_element(m_coordinatesToTile.cbegin(), m_coordinatesToTile.cend(),
                                            [](const auto& lhs, const auto& rhs)
                                            {
                                                return lhs.first.y < rhs.first.y;
                                            });

    m_minY = minmaxIters.first->first.y;
    m_maxY = minmaxIters.second->first.y;
}

void WaterFlowSimulator::run()
{
    startSpring(SPRING_START_POS);
}

unsigned WaterFlowSimulator::getNumTilesWithWater() const
{
    return std::count_if(m_coordinatesToTile.cbegin(), m_coordinatesToTile.cend(), [this](const auto& elem)
                            {
                                const Coordinates& coordinates = elem.first;
                                Tile tile = getTileAt(coordinates);

                                bool isWater = (tile == Tile::SETTLED_WATER || tile == Tile::FLOWING_WATER);
                                bool isInBounds = (coordinates.y >= m_minY) && (coordinates.y <= m_maxY);

                                return isWater && isInBounds;
                            });
}

unsigned WaterFlowSimulator::getNumTilesWithSettledWater() const
{
    return std::count_if(m_coordinatesToTile.cbegin(), m_coordinatesToTile.cend(), [this](const auto& elem)
                            {
                                return this->getTileAt(elem.first) == Tile::SETTLED_WATER;
                            });
}

void WaterFlowSimulator::startSpring(const Coordinates& springStartPos)
{
    for (int springCurrentY = springStartPos.y; springCurrentY <= m_maxY; ++springCurrentY)
    {
        setTileAt({springCurrentY, springStartPos.x}, Tile::FLOWING_WATER);

        if (getTileAt({springCurrentY + 1, springStartPos.x}) == Tile::FLOWING_WATER)
        {
            break;
        }

        if (!tileIsFreeAt({springCurrentY + 1, springStartPos.x}))
        {
            spreadHorizontallyAndUpwards({springCurrentY, springStartPos.x});
            break;
        }
    }
}

void WaterFlowSimulator::spreadHorizontallyAndUpwards(const Coordinates& spreadStartPos)
{
    for (int springCurrentY = spreadStartPos.y; springCurrentY >= m_minY; --springCurrentY)
    {
        spreadHorizontally({springCurrentY, spreadStartPos.x});

        if (getTileAt({springCurrentY, spreadStartPos.x}) != Tile::SETTLED_WATER)
        {
            break;
        }
    }
}

void WaterFlowSimulator::spreadHorizontally(const Coordinates& spreadStartPos)
{
    Coordinates leftBound = boundLeft(spreadStartPos);
    Coordinates rightBound = boundRight(spreadStartPos);

    if (!tileIsFreeAt(leftBound) && !tileIsFreeAt(rightBound))
    {
        fillUp(leftBound, rightBound, Tile::SETTLED_WATER);
    }
    else
    {
        fillUp(leftBound, rightBound, Tile::FLOWING_WATER);

        startSpringIfFree(leftBound);
        startSpringIfFree(rightBound);
    }
}

void WaterFlowSimulator::fillUp(const Coordinates& leftWall, const Coordinates& rightWall, Tile tileValue)
{
    int y = leftWall.y;
    for (int x = leftWall.x + 1; x < rightWall.x; ++x)
    {
        setTileAt({y, x}, tileValue);
    }
}

void WaterFlowSimulator::startSpringIfFree(const Coordinates& springStartPos)
{
    if (tileIsFreeAt(springStartPos))
    {
        startSpring(springStartPos);
    }
}

Coordinates WaterFlowSimulator::boundLeft(Coordinates coordinates)
{
    return iterateUntil(std::move(coordinates), [](Coordinates& c) {--c.x; });
}

Coordinates WaterFlowSimulator::boundRight(Coordinates coordinates)
{
    return iterateUntil(std::move(coordinates), [](Coordinates& c) {++c.x; });
}

Coordinates WaterFlowSimulator::iterateUntil(Coordinates coordinates, const std::function<void(Coordinates&)> iterFunc)
{
    while (true)
    {
        if (getTileAt({coordinates.y, coordinates.x}) == Tile::CLAY || tileIsFreeAt({coordinates.y + 1, coordinates.x}))
        {
            return {coordinates.y, coordinates.x};
        }

        iterFunc(coordinates);
    }
}


Tile WaterFlowSimulator::getTileAt(const Coordinates& coordinates) const
{
    const auto findResult = m_coordinatesToTile.find(coordinates);
    if (findResult == m_coordinatesToTile.cend())
    {
        return Tile::SAND;
    }

    return findResult->second;
}

bool WaterFlowSimulator::tileIsFreeAt(const Coordinates& coordinates) const
{
    Tile tile = getTileAt({coordinates.y, coordinates.x});
    return (tile == Tile::SAND || tile == Tile::FLOWING_WATER);
}

void WaterFlowSimulator::setTileAt(const Coordinates& coordinates, Tile newValue)
{
    m_coordinatesToTile[coordinates] = newValue;
}

}
}
}
