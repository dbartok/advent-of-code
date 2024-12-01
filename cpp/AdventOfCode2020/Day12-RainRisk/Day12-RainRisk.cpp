#include "Day12-RainRisk.h"

#include "ShipNavigator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day12
{

NavigationAction charToNavigationAction(char c)
{
    const static std::unordered_map<char, NavigationAction> mapping
    {
        {'F', NavigationAction::FORWARD},
        {'L', NavigationAction::LEFT},
        {'R', NavigationAction::RIGHT},
        {'N', NavigationAction::NORTH},
        {'S', NavigationAction::SOUTH},
        {'E', NavigationAction::EAST},
        {'W', NavigationAction::WEST},
    };

    return mapping.at(c);
}

NavigationInstruction parseInstruction(const std::string& instructionLine)
{
    const NavigationAction action = charToNavigationAction(instructionLine.front());
    const int value = std::stoi(instructionLine.substr(1));

    return NavigationInstruction{action, value};
}

std::vector<NavigationInstruction> parseInstructions(const std::vector<std::string>& instructionLines)
{
    std::vector<NavigationInstruction> instructions;

    for (const auto& line : instructionLines)
    {
        NavigationInstruction instruction = parseInstruction(line);
        instructions.push_back(std::move(instruction));
    }

    return instructions;
}

int distanceToEndLocationShipMoves(const std::vector<std::string>& instructionLines)
{
    std::vector<NavigationInstruction> instructions = parseInstructions(instructionLines);
    ShipNavigator shipNavigator{std::move(instructions)};
    shipNavigator.executeAllInstructions();
    return shipNavigator.getManhattanDistanceFromStart();
}

int distanceToEndLocationWaypointMoves(const std::vector<std::string>& instructionLines)
{
    std::vector<NavigationInstruction> instructions = parseInstructions(instructionLines);
    WaypointShipNavigator shipNavigator{std::move(instructions)};
    shipNavigator.executeAllInstructions();
    return shipNavigator.getManhattanDistanceFromStart();
}

}
}
}
