#include "TuringMachineState.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

TuringMachineState::TuringMachineState(StateIDType currentStateID, int cursorPos)
    : currentStateID{currentStateID}
    , cursorPos{cursorPos}
    , tapeTrueSet{}
{

}

}
