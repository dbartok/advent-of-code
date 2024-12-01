#include "Day19-NotEnoughMinerals.h"

#include "GeodeHarvestingSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int TOTAL_AVAILABLE_TIME_FIRST_PART = 24;
const int TOTAL_AVAILABLE_TIME_SECOND_PART = 32;
const size_t NUM_MAX_BLUEPRINTS_SECOND_PART = 3;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day19
{

MineralMatrix parseBlueprintLine(const std::string& blueprintLine)
{
    const std::regex blueprintLineRegex(R"(Blueprint [0-9]+: Each ore robot costs ([0-9]+) ore. Each clay robot costs ([0-9]+) ore. Each obsidian robot costs ([0-9]+) ore and ([0-9]+) clay. Each geode robot costs ([0-9]+) ore and ([0-9]+) obsidian.)");
    std::smatch blueprintLineMatch;

    std::regex_match(blueprintLine, blueprintLineMatch, blueprintLineRegex);

    const int oreRobotOreCost = std::stoi(blueprintLineMatch[1]);
    const int clayRobotOreCost = std::stoi(blueprintLineMatch[2]);
    const int obsidianRobotOreCost = std::stoi(blueprintLineMatch[3]);
    const int obsidianRobotClayCost = std::stoi(blueprintLineMatch[4]);
    const int geodeRobotOreCost = std::stoi(blueprintLineMatch[5]);
    const int geodeRobotObsidianCost = std::stoi(blueprintLineMatch[6]);

    MineralMatrix robotCostMatrix{0};

    robotCostMatrix.at(ORE_INDEX).at(ORE_INDEX) = oreRobotOreCost;
    robotCostMatrix.at(CLAY_INDEX).at(ORE_INDEX) = clayRobotOreCost;
    robotCostMatrix.at(OBSIDIAN_INDEX).at(ORE_INDEX) = obsidianRobotOreCost;
    robotCostMatrix.at(OBSIDIAN_INDEX).at(CLAY_INDEX) = obsidianRobotClayCost;
    robotCostMatrix.at(GEODE_INDEX).at(ORE_INDEX) = geodeRobotOreCost;
    robotCostMatrix.at(GEODE_INDEX).at(OBSIDIAN_INDEX) = geodeRobotObsidianCost;

    return robotCostMatrix;
}

std::vector<MineralMatrix> parseBlueprintLines(const std::vector<std::string>& blueprintLines)
{
    std::vector<MineralMatrix> robotCostMatrices;

    for (const auto& blueprintLine : blueprintLines)
    {
        MineralMatrix robotCostMatrix = parseBlueprintLine(blueprintLine);
        robotCostMatrices.push_back(std::move(robotCostMatrix));
    }

    return robotCostMatrices;
}

int sumOfBlueprintQualityLevels(const std::vector<std::string>& blueprintLines)
{
    std::vector<MineralMatrix> robotCostMatrices = parseBlueprintLines(blueprintLines);
    int totalQualityLevel = 0;

    for (size_t i = 0; i < robotCostMatrices.size(); ++i)
    {
        GeodeHarvestingSimulator geodeHarvestingSimulator{std::move(robotCostMatrices.at(i)), TOTAL_AVAILABLE_TIME_FIRST_PART};
        geodeHarvestingSimulator.simulate();
        const int maxNumGeodesHarvested = geodeHarvestingSimulator.getMaxNumGeodesHarvested();
        const int qualityLevel = maxNumGeodesHarvested * (i + 1);

        totalQualityLevel += qualityLevel;
    }

    return totalQualityLevel;
}

int productOfFirstFewBlueprintMaxGeodesWithMoreTime(const std::vector<std::string>& blueprintLines)
{
    std::vector<MineralMatrix> robotCostMatrices = parseBlueprintLines(blueprintLines);
    int productOfMaxGeodes = 1;

    for (size_t i = 0; i < robotCostMatrices.size() && i < NUM_MAX_BLUEPRINTS_SECOND_PART; ++i)
    {
        GeodeHarvestingSimulator geodeHarvestingSimulator{std::move(robotCostMatrices.at(i)), TOTAL_AVAILABLE_TIME_SECOND_PART};
        geodeHarvestingSimulator.simulate();
        const int maxNumGeodesHarvested = geodeHarvestingSimulator.getMaxNumGeodesHarvested();

        productOfMaxGeodes *= maxNumGeodesHarvested;
    }

    return productOfMaxGeodes;
}

}
}
}