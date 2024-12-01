#pragma once

#include <AdventOfCode2019/Day05-SunnyWithAsteroids/IntcodeInterpreter.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day15
{

using AdventOfCode::Year2019::Day05::IntcodeInterpreter;

using Coordinates = std::pair<int, int>;

using CoordinatesToDistance = std::unordered_map<Coordinates, int, boost::hash<Coordinates>>;

enum class DroidStatusCode
{
    HIT_WALL = 0,
    MOVED = 1,
    MOVED_AND_OXYGEN_FOUND = 2,
};

enum class Direction
{
    NORTH = 1,
    SOUTH = 2,
    WEST = 3,
    EAST = 4,
};

class OxygenRepairDroid
{
public:
    OxygenRepairDroid(IntcodeInterpreter interpreter);

    void traverse();
    void moveToOxygen();

    int getDistanceToOxygen() const;
    int getMaxDistance() const;

private:
    IntcodeInterpreter m_interpreter;

    Coordinates m_currentPosition;
    int m_numStepsFromStart;
    CoordinatesToDistance m_coordinatesToDistance;

    Coordinates m_oxygenCoordinates;

    bool m_halted = false;

    void traverseRecursive(bool shouldHaltOnOxygen = false);
    DroidStatusCode tryMove(Direction direction);
    bool updateDataAfterMove(Direction direction);
    void updatePosition(Direction direction);
    bool updateMap();
    void undoMove(Direction direction);
    bool isHalted() const;

    static std::vector<Direction> getAllDirections();
    static Direction getOppositeDirection(Direction direction);
};

}
}
}
