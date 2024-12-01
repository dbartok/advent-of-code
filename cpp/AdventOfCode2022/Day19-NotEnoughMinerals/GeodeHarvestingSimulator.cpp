#include "GeodeHarvestingSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <array>
#include <regex>
#include <unordered_set>
#include <stack>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const AdventOfCode::Year2022::Day19::MineralArray INITIAL_MINERAL_PRODUCTION = {1, 0, 0, 0};
const AdventOfCode::Year2022::Day19::MineralArray ZERO_MINERAL_ARRAY = {0, 0, 0, 0};

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day19
{



const MineralArray INITIAL_MINERAL_PRODUCTION = {1, 0, 0, 0};
const MineralArray ZERO_MINERAL_ARRAY = {0, 0, 0, 0};

GeodeHarvestingSimulator::GeodeHarvestingSimulator(MineralMatrix robotCostMatrix, int totalAvailableTime)
    : m_robotCostMatrix{std::move(robotCostMatrix)}
    , m_totalAvailableTime{totalAvailableTime}
    , m_maxMineralCosts{ZERO_MINERAL_ARRAY}
{
    for (const auto& cost : m_robotCostMatrix)
    {
        for (size_t i = 0; i < NUM_MINERAL_TYPES; ++i)
        {
            m_maxMineralCosts.at(i) = std::max(m_maxMineralCosts.at(i), cost.at(i));
        }
    }
}

void GeodeHarvestingSimulator::simulate()
{
    std::stack<State> stateStack;
    State startState = {INITIAL_MINERAL_PRODUCTION, ZERO_MINERAL_ARRAY, m_totalAvailableTime};
    stateStack.push(startState);
    StateSet seenStates{startState};

    while (!stateStack.empty())
    {
        const State currentState = stateStack.top();
        stateStack.pop();

        std::vector<State> nextStates = getNextStates(currentState);
        std::vector<State> prunedNextStates = pruneNextStates(std::move(nextStates));

        for (auto& nextState : prunedNextStates)
        {
            m_maxNumGeodesHarvested = std::max(m_maxNumGeodesHarvested, nextState.mineralsAvailable.at(GEODE_INDEX));
            if (seenStates.insert(nextState).second)
            {
                stateStack.push(std::move(nextState));
            }
        }
    }
}

int GeodeHarvestingSimulator::getMaxNumGeodesHarvested() const
{
    return m_maxNumGeodesHarvested;
}

std::vector<GeodeHarvestingSimulator::State> GeodeHarvestingSimulator::getNextStates(const State& currentState) const
{
    if (currentState.remainingTime == 0)
    {
        return {};
    }

    std::vector<State> nextStates;

    // Build
    for (size_t robotToBuildIndex = 0; robotToBuildIndex < NUM_MINERAL_TYPES; ++robotToBuildIndex)
    {
        // No time to benefit from build
        if (currentState.remainingTime == 1 || (currentState.remainingTime == 2 && robotToBuildIndex != GEODE_INDEX))
        {
            continue;
        }

        if (canAffordToBuild(currentState, robotToBuildIndex))
        {
            auto newState{currentState};
            elapseMinute(newState);
            build(newState, robotToBuildIndex);
            nextStates.push_back(std::move(newState));
        }
    }

    // Wait
    auto newState{currentState};
    elapseMinute(newState);
    nextStates.push_back(std::move(newState));

    return nextStates;
}

std::vector<GeodeHarvestingSimulator::State> GeodeHarvestingSimulator::pruneNextStates(std::vector<State> nextStates) const
{
    std::vector<State> prunedNextStates;

    std::copy_if(std::make_move_iterator(nextStates.begin()), std::make_move_iterator(nextStates.end()), std::back_inserter(prunedNextStates), [this](const State& state)
                    {
                        return !this->isOverproducing(state) && this->canStillExceedBestSoFar(state);
                    });

    return prunedNextStates;
}

bool GeodeHarvestingSimulator::canAffordToBuild(const State& state, size_t robotToBuildIndex) const
{
    const auto& robotCost = m_robotCostMatrix.at(robotToBuildIndex);
    for (size_t i = 0; i < NUM_MINERAL_TYPES; ++i)
    {
        if (state.mineralsAvailable.at(i) < robotCost.at(i))
        {
            return false;
        }
    }

    return true;
}

void GeodeHarvestingSimulator::build(GeodeHarvestingSimulator::State& state, size_t robotToBuildIndex) const
{
    const auto& robotCost = m_robotCostMatrix.at(robotToBuildIndex);
    for (size_t i = 0; i < NUM_MINERAL_TYPES; ++i)
    {
        state.mineralsAvailable.at(i) -= robotCost.at(i);
    }

    ++state.mineralProduction.at(robotToBuildIndex);
}

bool GeodeHarvestingSimulator::isOverproducing(const State& state) const
{
    for (size_t i = 0; i < NUM_MINERAL_TYPES; ++i)
    {
        if (i == GEODE_INDEX)
        {
            continue;
        }

        if (state.mineralProduction.at(i) > m_maxMineralCosts.at(i))
        {
            return true;
        }
    }

    return false;
}

bool GeodeHarvestingSimulator::canStillExceedBestSoFar(const State& state) const
{
    const int currentNumGeodes = state.mineralsAvailable.at(GEODE_INDEX);
    const int geodeProduction = state.mineralProduction.at(GEODE_INDEX);

    const int numGeodesAtEndWithCurrentProduction = currentNumGeodes + geodeProduction * state.remainingTime;

    const int remainingProductionTime = state.remainingTime - 1;
    const int numMaxGeodesProducedByNewRobots = remainingProductionTime * (remainingProductionTime + 1) / 2;

    return numGeodesAtEndWithCurrentProduction + numMaxGeodesProducedByNewRobots > m_maxNumGeodesHarvested;
}

void GeodeHarvestingSimulator::elapseMinute(State& state)
{
    for (size_t i = 0; i < NUM_MINERAL_TYPES; ++i)
    {
        state.mineralsAvailable.at(i) += state.mineralProduction.at(i);
    }

    --state.remainingTime;
}

}
}
}
