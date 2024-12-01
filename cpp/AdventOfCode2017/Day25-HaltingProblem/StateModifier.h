#pragma once

#include "TuringMachineState.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day25
{

class StateModifier
{
public:
    StateModifier(bool writtenValue, int cursorOffset, StateIDType nextStateID) noexcept;
    void modify(TuringMachineState& state) const;

private:
    bool m_writtenValue;
    int m_cursorOffset;
    StateIDType m_nextStateID;
};

}
}
}
