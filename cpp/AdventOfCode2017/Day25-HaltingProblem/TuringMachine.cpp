#include "TuringMachine.h"

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

TuringMachine::TuringMachine(TransitionMap stateIDToTransition, StateIDType startingStateID, unsigned numIterations)
    : m_stateIDToTransition{std::move(stateIDToTransition)}
    , m_state{startingStateID, 0}
    , m_numIterations{numIterations}
{

}

void TuringMachine::run()
{
    for (unsigned i = 0; i < m_numIterations; ++i)
    {
        const StateTransition currentStateTransition = m_stateIDToTransition.at(m_state.currentStateID);
        currentStateTransition.apply(m_state);
    }
}

unsigned TuringMachine::getChecksum() const noexcept
{
    return m_state.tapeTrueSet.size();
}

}
}
}
