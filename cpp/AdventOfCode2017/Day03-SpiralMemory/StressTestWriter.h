#pragma once

#include "InfiniteGrid.h"
#include "Head.h"

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

class StressTestWriter
{
public:
    StressTestWriter();
    void writeUntil(unsigned threshold);
    unsigned getLastWritten() const noexcept;

private:
    InfiniteGrid<unsigned> m_grid;
    unsigned m_lastWritten;

    Head m_head;
    unsigned m_totalStepsUntilTurn;
    unsigned m_remainingStepsUntilTurn;

    void executeNextTurn() noexcept;
};

}
}
}
