#include "Head.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cassert>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day03
{

Head::Head(std::pair<int, int> position, Direction direction) noexcept
    : m_position{std::move(position)}
    , m_direction{direction}
{

}

const std::pair<int, int>& Head::getPosition() const noexcept
{
    return m_position;
}

Direction Head::getDirection() const noexcept
{
    return m_direction;
}

void Head::step() noexcept
{
    switch (m_direction)
    {
        case Direction::LEFT:
            m_position.first -= 1;
            break;
        case Direction::RIGHT:
            m_position.first += 1;
            break;
        case Direction::UP:
            m_position.second += 1;
            break;
        case Direction::DOWN:
            m_position.second -= 1;
            break;
        default:
            // Enum has invalid value
            assert(false);
    }
}

void Head::turnLeft() noexcept
{
    switch (m_direction)
    {
        case Direction::LEFT:
            m_direction = Direction::DOWN;
            break;
        case Direction::RIGHT:
            m_direction = Direction::UP;
            break;
        case Direction::UP:
            m_direction = Direction::LEFT;
            break;
        case Direction::DOWN:
            m_direction = Direction::RIGHT;
            break;
        default:
            // Enum has invalid value
            assert(false);
    }
}

}
}
}
