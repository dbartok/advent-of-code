#pragma once

#include "TuringMachineState.h"
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

class StateTransition
{
public:
    StateTransition(StateModifier valueFalseModifier, StateModifier valueTrueModifier) noexcept;
    void apply(TuringMachineState& state) const;

private:
    StateModifier m_valueFalseModifier;
    StateModifier m_valueTrueModifier;
};

}
}
}
