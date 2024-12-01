#include "FlowRateOptimizer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day16
{

FlowRateOptimizer::FlowRateOptimizer(CostMatrix costMatrix, std::unordered_map<size_t, int> roomIndexToFlowRate, int availableTime)
    : m_costMatrix{std::move(costMatrix)}
    , m_roomIndexToFlowRate{std::move(roomIndexToFlowRate)}
    , m_availableTime{availableTime}
{
    for (const auto& roomIndexAndFlowRate : m_roomIndexToFlowRate)
    {
        if (roomIndexAndFlowRate.second != 0)
        {
            m_roomIndicesWithNonZeroFlowRate.push_back(roomIndexAndFlowRate.first);
        }
    }
}

void FlowRateOptimizer::createAllStates()
{
    StateSet openStates;
    State startState{START_ROOM_INDEX, m_availableTime, {}, 0};
    openStates.insert(startState);

    while (!openStates.empty())
    {
        StateSet nextOpenStates;

        for (const auto& currentState : openStates)
        {
            std::vector<State> nextStates = getNextStates(currentState);

            for (const auto& nextState : nextStates)
            {
                insertKeepingHigherTotalPressureReleased(nextOpenStates, nextState);
                insertKeepingHigherTotalPressureReleased(m_allSeenStates, nextState);
            }
        }

        openStates = nextOpenStates;
    }
}

int FlowRateOptimizer::getMaxPressureReleasedWithOneWorker() const
{
    const auto maxPressureReleasedStateIter = std::max_element(m_allSeenStates.cbegin(), m_allSeenStates.cend(), [](const auto& lhs, const auto& rhs)
                                                                {
                                                                    return lhs.totalPressureReleased < rhs.totalPressureReleased;
                                                                });

    return maxPressureReleasedStateIter->totalPressureReleased;
}

int FlowRateOptimizer::getMaxPressureReleasedWithTwoWorkers() const
{
    int maxPressureReleased = 0;

    for (const auto& firstWorkerState : m_allSeenStates)
    {
        for (const auto& secondWorkerState : m_allSeenStates)
        {
            const auto visitedRoomIntersection = firstWorkerState.visitedRoomIndices & secondWorkerState.visitedRoomIndices;
            if (visitedRoomIntersection.none())
            {
                const int pressureReleased = firstWorkerState.totalPressureReleased + secondWorkerState.totalPressureReleased;
                maxPressureReleased = std::max(maxPressureReleased, pressureReleased);
            }
        }
    }

    return maxPressureReleased;
}

std::vector<FlowRateOptimizer::State> FlowRateOptimizer::getNextStates(const State& currentState) const
{
    std::vector<State> nextStates;

    for (const size_t nextRoomIndex : m_roomIndicesWithNonZeroFlowRate)
    {
        if (currentState.visitedRoomIndices.test(nextRoomIndex))
        {
            continue;
        }

        const int distanceToNextRoom = m_costMatrix.at(currentState.currentRoomIndex).at(nextRoomIndex);
        const int remainingTimeAfterNextValveOpen = currentState.remainingTime - distanceToNextRoom - 1;

        // No time for any newly opened valve to release pressure
        if (remainingTimeAfterNextValveOpen < 1)
        {
            continue;
        }

        auto newVisitedRoomIndices{currentState.visitedRoomIndices};
        newVisitedRoomIndices.set(nextRoomIndex);

        const int currentRoomFlowRate = m_roomIndexToFlowRate.at(nextRoomIndex);
        const int newTotalPressureReleased = currentState.totalPressureReleased + remainingTimeAfterNextValveOpen * currentRoomFlowRate;

        State nextState{nextRoomIndex, remainingTimeAfterNextValveOpen, newVisitedRoomIndices, newTotalPressureReleased};

        nextStates.push_back(std::move(nextState));
    }

    return nextStates;
}

void FlowRateOptimizer::insertKeepingHigherTotalPressureReleased(StateSet& states, State newState)
{
    auto insertionResult = states.insert(newState);
    if (!insertionResult.second)
    {
        auto existingStateIter = insertionResult.first;
        if (newState.totalPressureReleased > existingStateIter->totalPressureReleased)
        {
            states.erase(existingStateIter);
            states.insert(std::move(newState));
        }
    }
}

}
}
}
