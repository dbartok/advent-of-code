#include "StateModifier.h"

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

StateModifier::StateModifier(bool writtenValue, int cursorOffset, StateIDType nextStateID) noexcept
    : m_writtenValue{writtenValue}
    , m_cursorOffset{cursorOffset}
    , m_nextStateID{nextStateID}
{

}

void StateModifier::modify(TuringMachineState& state) const
{
    if (m_writtenValue)
    {
        state.tapeTrueSet.insert(state.cursorPos);
    }
    else
    {
        state.tapeTrueSet.erase(state.cursorPos);
    }

    state.cursorPos += m_cursorOffset;

    state.currentStateID = m_nextStateID;
}

}
}
}
