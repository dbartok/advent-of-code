#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <utility>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day03
{

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Head
{
public:
    Head(std::pair<int, int> m_position, Direction m_direction) noexcept;

    const std::pair<int, int>& getPosition() const noexcept;
    Direction getDirection() const noexcept;

    void step() noexcept;
    void turnLeft() noexcept;

private:
    std::pair<int, int> m_position;
    Direction m_direction;
};

}
}
}
