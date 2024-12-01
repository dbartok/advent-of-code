#include "Day12-SubterraneanSustainability.h"

#include "PlantNeighborSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const char PLANT_IDENTIFIER = '#';
const unsigned NUM_GROWTH_CYCLES_SHORT = 20;
const unsigned long long NUM_GROWTH_CYCLES_LONG = 50'000'000'000;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day12
{

Pots parseInitialPotsWithPlants(const std::string& initialStateLine)
{
    Pots initialPotsWithPlants;

    std::vector<std::string> tokens;
    boost::split(tokens, initialStateLine, boost::is_any_of(":"), boost::token_compress_on);

    boost::trim(tokens[1]);
    const std::string& initialPotsWithPlantsString = tokens[1];

    for (size_t i = 0; i < initialPotsWithPlantsString.length(); ++i)
    {
        if (initialPotsWithPlantsString[i] == PLANT_IDENTIFIER)
        {
            initialPotsWithPlants.insert(i);
        }
    }

    return initialPotsWithPlants;
}

NeighborPattern parseNeighborPattern(const std::string& neighborPatternString)
{
    NeighborPattern neighborPattern{};

    for (size_t i = 0; i < neighborPatternString.length(); ++i)
    {
        const bool isPlant = (neighborPatternString[i] == '#');
        neighborPattern[i] = isPlant;
    }

    return neighborPattern;
}

std::vector<NeighborPattern> parseNeighborPatternsResultingInPlant(const std::vector<std::string>& neighborPatternLines)
{
    std::vector<NeighborPattern> neighborPatternsResultingInPlant;

    for (const auto& lines : neighborPatternLines)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, lines, boost::is_any_of(" =>"), boost::token_compress_on);

        const bool isResultPlant = (tokens[1].front() == PLANT_IDENTIFIER);
        if (isResultPlant)
        {
            neighborPatternsResultingInPlant.push_back(parseNeighborPattern(tokens[0]));
        }
    }

    return neighborPatternsResultingInPlant;
}

long long sumOfPotNumbersWithPlantAfterGrowthGivenTime(const std::string& initialStateLine, const std::vector<std::string>& neighborPatternLines, unsigned long long numCycles)
{
    Pots initialPotsWithPlants = parseInitialPotsWithPlants(initialStateLine);
    std::vector<NeighborPattern> neighborPatterns = parseNeighborPatternsResultingInPlant(neighborPatternLines);

    PlantNeighborSimulator simulator{std::move(initialPotsWithPlants), std::move(neighborPatterns)};

    simulator.simulateGrowth(numCycles);

    return simulator.getSumOfPotNumbersWithPlant();
}

long long sumOfPotNumbersWithPlantAfterGrowthShortTime(const std::string& initialStateLine, const std::vector<std::string>& neighborPatternLines)
{
    return sumOfPotNumbersWithPlantAfterGrowthGivenTime(initialStateLine, neighborPatternLines, NUM_GROWTH_CYCLES_SHORT);
}

long long sumOfPotNumbersWithPlantAfterGrowthLongTime(const std::string& initialStateLine, const std::vector<std::string>& neighborPatternLines)
{
    return sumOfPotNumbersWithPlantAfterGrowthGivenTime(initialStateLine, neighborPatternLines, NUM_GROWTH_CYCLES_LONG);
}

}
}
}
