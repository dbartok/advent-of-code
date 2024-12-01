#include "StressTestWriter.h"

#include "InfiniteGridUtil.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day03
{

StressTestWriter::StressTestWriter()
    : m_grid{}
    , m_lastWritten{0}
    , m_head{std::make_pair(0, 0), Direction::RIGHT}
    , m_remainingStepsUntilTurn{1}
    , m_totalStepsUntilTurn{1}
{
    m_grid.setValue(0, 0, 1);
}

void StressTestWriter::writeUntil(unsigned threshold)
{
    while (true)
    {
        if (m_remainingStepsUntilTurn == 0)
        {
            executeNextTurn();
        }

        m_head.step();

        unsigned value = sumOfAllNeighbors(m_grid, m_head.getPosition());
        if (value > threshold)
        {
            m_lastWritten = value;
            break;
        }

        m_grid.setValue(m_head.getPosition().first, m_head.getPosition().second, value);

        --m_remainingStepsUntilTurn;
    }
}

unsigned StressTestWriter::getLastWritten() const noexcept
{
    return m_lastWritten;
}

void StressTestWriter::executeNextTurn() noexcept
{
    if (m_head.getDirection() == Direction::DOWN || m_head.getDirection() == Direction::UP)
    {
        ++m_totalStepsUntilTurn;
    }

    m_remainingStepsUntilTurn = m_totalStepsUntilTurn;
    m_head.turnLeft();
}

}
}
}
