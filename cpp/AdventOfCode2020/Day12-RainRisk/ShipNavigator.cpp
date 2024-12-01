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

ShipNavigator::ShipNavigator(std::vector<NavigationInstruction> navigationInstructions)
    : ShipNavigator(std::move(navigationInstructions), {1, 0})
{

}

ShipNavigator::~ShipNavigator()
{

}

void ShipNavigator::executeAllInstructions()
{
    for (const auto& instruction : m_navigationInstructions)
    {
        m_actionToFunc.at(instruction.action)(instruction.value);
    }
}

int ShipNavigator::getManhattanDistanceFromStart() const
{
    return m_positionVector.cwiseAbs().sum();
}

ShipNavigator::ShipNavigator(std::vector<NavigationInstruction> navigationInstructions, Vector2D directionVector)
    : m_positionVector{0, 0}
    , m_directionVector{std::move(directionVector)}
    , m_navigationInstructions{std::move(navigationInstructions)}
{
    m_actionToFunc =
    {
        {NavigationAction::FORWARD, [this](int value) {this->moveForward(value); }},
        {NavigationAction::LEFT, [this](int value) {this->turnLeft(value); }},
        {NavigationAction::RIGHT, [this](int value) {this->turnRight(value); }},
        {NavigationAction::NORTH, [this](int value) {this->moveNorth(value); }},
        {NavigationAction::SOUTH, [this](int value) {this->moveSouth(value); }},
        {NavigationAction::EAST, [this](int value) {this->moveEast(value); }},
        {NavigationAction::WEST, [this](int value) {this->moveWest(value); }},
    };
}

void ShipNavigator::moveNorth(int value)
{
    m_positionVector += Vector2D{0, 1} *value;
}

void ShipNavigator::moveSouth(int value)
{
    m_positionVector += Vector2D{0, -1} *value;
}

void ShipNavigator::moveEast(int value)
{
    m_positionVector += Vector2D{1, 0} *value;
}

void ShipNavigator::moveWest(int value)
{
    m_positionVector += Vector2D{-1, 0} *value;
}


void ShipNavigator::moveForward(int value)
{
    m_positionVector += m_directionVector * value;
}

void ShipNavigator::turnLeft(int value)
{
    while ((value -= 90) >= 0)
    {
        m_directionVector[1] *= -1;
        std::swap(m_directionVector[0], m_directionVector[1]);
    }
}

void ShipNavigator::turnRight(int value)
{
    turnLeft(360 - value);
}

WaypointShipNavigator::WaypointShipNavigator(std::vector<NavigationInstruction> navigationInstructions)
    : ShipNavigator(std::move(navigationInstructions), {10, 1})
{

}

void WaypointShipNavigator::moveNorth(int value)
{
    m_directionVector += Vector2D{0, 1} *value;
}

void WaypointShipNavigator::moveSouth(int value)
{
    m_directionVector += Vector2D{0, -1} *value;
}

void WaypointShipNavigator::moveEast(int value)
{
    m_directionVector += Vector2D{1, 0} *value;
}

void WaypointShipNavigator::moveWest(int value)
{
    m_directionVector += Vector2D{-1, 0} *value;
}

}
}
}
