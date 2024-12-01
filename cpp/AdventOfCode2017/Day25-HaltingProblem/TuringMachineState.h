#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day25
{

using StateIDType = char;

struct TuringMachineState
{
    StateIDType currentStateID;
    int cursorPos;
    std::unordered_set<int> tapeTrueSet;

    TuringMachineState(StateIDType currentStateID, int cursorPos);
};

}
}
}
