#pragma once

#include "TuringMachineState.h"
#include "StateTransition.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day25
{

class TuringMachine
{
public:
    using TransitionMap = std::unordered_map<StateIDType, StateTransition>;

    TuringMachine(TransitionMap stateIDToTransition, StateIDType startingStateID, unsigned numIterations);
    void run();
    unsigned getChecksum() const noexcept;

private:
    TransitionMap m_stateIDToTransition;

    TuringMachineState m_state;
    unsigned m_numIterations;
};

}
}
}
