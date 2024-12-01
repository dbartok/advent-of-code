#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <array>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day19
{

const size_t ORE_INDEX = 0;
const size_t CLAY_INDEX = 1;
const size_t OBSIDIAN_INDEX = 2;
const size_t GEODE_INDEX = 3;
const size_t NUM_MINERAL_TYPES = 4;
using MineralArray = std::array<int, NUM_MINERAL_TYPES>;
using MineralMatrix = std::array<MineralArray, NUM_MINERAL_TYPES>;

class GeodeHarvestingSimulator
{
public:
    GeodeHarvestingSimulator(MineralMatrix robotCostMatrix, int totalAvailableTime);

    void simulate();

    int getMaxNumGeodesHarvested() const;

private:
    struct State
    {
        MineralArray mineralProduction;
        MineralArray mineralsAvailable;
        int remainingTime;

        bool operator==(const State& other) const
        {
            return mineralProduction == other.mineralProduction &&
                mineralsAvailable == other.mineralsAvailable &&
                remainingTime == other.remainingTime;
        }
    };

    struct StateHash
    {
        std::size_t operator()(const State& state) const
        {
            std::size_t seed = 0;

            boost::hash_combine(seed, state.mineralProduction);
            boost::hash_combine(seed, state.mineralsAvailable);
            boost::hash_combine(seed, state.remainingTime);

            return seed;
        }
    };

    using StateSet = std::unordered_set<State, StateHash>;

    MineralMatrix m_robotCostMatrix;
    int m_totalAvailableTime;
    MineralArray m_maxMineralCosts;

    int m_maxNumGeodesHarvested = 0;

    std::vector<State> getNextStates(const State& currentState) const;
    std::vector<State> pruneNextStates(std::vector<State> nextStates) const;
    bool canAffordToBuild(const State& state, size_t robotToBuildIndex) const;
    void build(State& state, size_t robotToBuildIndex) const;
    bool isOverproducing(const State& state) const;
    bool canStillExceedBestSoFar(const State& state) const;

    static void elapseMinute(State& state);
};

}
}
}
