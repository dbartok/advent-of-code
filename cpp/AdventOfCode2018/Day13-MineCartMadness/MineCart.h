#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <utility>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day13
{

using Coordinates = std::pair<unsigned, unsigned>;

enum class Orientation
{
    LEFT = 0,
    DOWN = 1,
    RIGHT = 2,
    UP = 3,
};

enum class Turn
{
    LEFT = 1,
    STRAIGHT = 0,
    RIGHT = 3,
};

class MineCart
{
public:
    MineCart(Orientation orientation, Coordinates position);

    Orientation getCurrentOrientation() const;
    Coordinates getCurrentPosition() const;

    void setCurrentOrientation(Orientation orientation);

    void turnToNextOrientation();
    void move();

private:
    Orientation m_orientation;
    Coordinates m_position;
    Turn m_nextTurn;
};

}
}
}
