#include "Day17-PyroclasticFlow.h"

#include "FallingRockSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned NUM_ROCKS_FIRST_PART = 2022;
const uint64_t NUM_ROCKS_SECOND_PART = 1'000'000'000'000;

}
namespace AdventOfCode
{
namespace Year2022
{
namespace Day17
{

std::vector<Direction> parseJetPatternString(const std::string& jetPatternString)
{
    std::vector<Direction> jetPattern;

    for (const char c : jetPatternString)
    {
        if (c == '<')
        {
            jetPattern.push_back(Direction::LEFT);
        }
        else if (c == '>')
        {
            jetPattern.push_back(Direction::RIGHT);
        }
        else
        {
            throw std::runtime_error("Invalid character: " + std::string{c});
        }
    }

    return jetPattern;
}

int64_t getTowerHeightForGivenNumRocks(const std::string& jetPatternString, uint64_t numRocks)
{
    std::vector<Direction> jetPattern = parseJetPatternString(jetPatternString);

    FallingRockSimulator fallingRockSimulator{std::move(jetPattern), numRocks};

    fallingRockSimulator.simulate();

    return fallingRockSimulator.getTowerHeight();
}

int64_t towerHeightAfterRocksStoppedFalling(const std::string& jetPatternString)
{
    return getTowerHeightForGivenNumRocks(jetPatternString, NUM_ROCKS_FIRST_PART);
}

int64_t towerHeightAfterRocksStoppedFallingWithManyRocks(const std::string& jetPatternString)
{
    return getTowerHeightForGivenNumRocks(jetPatternString, NUM_ROCKS_SECOND_PART);
}

}
}
}