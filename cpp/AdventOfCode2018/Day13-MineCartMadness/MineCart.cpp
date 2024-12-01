#include "MineCart.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day13
{

MineCart::MineCart(Orientation orientation, Coordinates position)
    : m_orientation{orientation}
    , m_position{position}
    , m_nextTurn{Turn::LEFT}
{

}

Orientation MineCart::getCurrentOrientation() const
{
    return m_orientation;
}

Coordinates MineCart::getCurrentPosition() const
{
    return m_position;
}

void MineCart::setCurrentOrientation(Orientation orientation)
{
    m_orientation = orientation;
}

void MineCart::turnToNextOrientation()
{
    m_orientation = static_cast<Orientation>((static_cast<unsigned>(m_orientation) + static_cast<unsigned>(m_nextTurn)) % 4);

    if (m_nextTurn == Turn::LEFT)
    {
        m_nextTurn = Turn::STRAIGHT;
    }
    else if (m_nextTurn == Turn::STRAIGHT)
    {
        m_nextTurn = Turn::RIGHT;
    }
    else if (m_nextTurn == Turn::RIGHT)
    {
        m_nextTurn = Turn::LEFT;
    }
}

void MineCart::move()
{
    switch (m_orientation)
    {
        case Orientation::LEFT:
            m_position.first -= 1;
            break;

        case Orientation::RIGHT:
            m_position.first += 1;
            break;

        case Orientation::UP:
            m_position.second -= 1;
            break;

        case Orientation::DOWN:
            m_position.second += 1;
            break;
    }
}

}
}
}
