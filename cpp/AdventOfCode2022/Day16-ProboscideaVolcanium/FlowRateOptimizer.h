#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_map>
#include <unordered_set>
#include <bitset>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const size_t MAX_NUM_RELEVANT_ROOMS = 75;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day16
{

const size_t START_ROOM_INDEX = 0;

using CostMatrixRow = std::vector<int>;
using CostMatrix = std::vector<CostMatrixRow>;

class FlowRateOptimizer
{
public:
    FlowRateOptimizer(CostMatrix costMatrix, std::unordered_map<size_t, int> roomIndexToFlowRate, int availableTime);

    void createAllStates();

    int getMaxPressureReleasedWithOneWorker() const;
    int getMaxPressureReleasedWithTwoWorkers() const;

private:
    struct State
    {
        size_t currentRoomIndex;
        int remainingTime;
        std::bitset<MAX_NUM_RELEVANT_ROOMS> visitedRoomIndices;

        int totalPressureReleased;

        bool operator==(const State& other) const
        {
            return currentRoomIndex == other.currentRoomIndex &&
                remainingTime == other.remainingTime &&
                visitedRoomIndices == other.visitedRoomIndices;
        }
    };

    struct StateHash
    {
        std::size_t operator()(const State& state) const
        {
            std::size_t seed = 0;

            boost::hash_combine(seed, state.currentRoomIndex);
            boost::hash_combine(seed, state.remainingTime);
            boost::hash_combine(seed, state.visitedRoomIndices.to_ullong());

            return seed;
        }
    };

    using StateSet = std::unordered_set<State, StateHash>;

    CostMatrix m_costMatrix;
    std::unordered_map<size_t, int> m_roomIndexToFlowRate;
    int m_availableTime;
    std::vector<size_t> m_roomIndicesWithNonZeroFlowRate;

    StateSet m_allSeenStates;

    std::vector<State> getNextStates(const State& currentState) const;

    static void insertKeepingHigherTotalPressureReleased(StateSet& states, State newState);
};


}
}
}
