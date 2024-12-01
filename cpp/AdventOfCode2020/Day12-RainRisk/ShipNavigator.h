#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>

#include <vector>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day12
{

using Vector2D = Eigen::Matrix<int, 2, 1>;

enum class NavigationAction
{
    FORWARD,
    LEFT,
    RIGHT,
    NORTH,
    SOUTH,
    EAST,
    WEST,
};

struct NavigationInstruction
{
    NavigationAction action;
    int value;
};

class ShipNavigator
{
public:
    ShipNavigator(std::vector<NavigationInstruction> navigationInstructions);
    virtual ~ShipNavigator();

    void executeAllInstructions();

    int getManhattanDistanceFromStart() const;

protected:
    Vector2D m_positionVector;
    Vector2D m_directionVector;

    ShipNavigator(std::vector<NavigationInstruction> navigationInstructions, Vector2D directionVector);

    virtual void moveNorth(int value);
    virtual void moveSouth(int value);
    virtual void moveEast(int value);
    virtual void moveWest(int value);

private:
    std::vector<NavigationInstruction> m_navigationInstructions;
    std::unordered_map<NavigationAction, std::function<void(int)>> m_actionToFunc;

    void moveForward(int value);
    void turnLeft(int value);
    void turnRight(int value);
};

class WaypointShipNavigator : public ShipNavigator
{
public:
    WaypointShipNavigator(std::vector<NavigationInstruction> navigationInstructions);

protected:
    void moveNorth(int value) override;
    void moveSouth(int value) override;
    void moveEast(int value) override;
    void moveWest(int value) override;
};

}
}
}
