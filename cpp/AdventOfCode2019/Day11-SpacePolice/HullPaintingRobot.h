#pragma once

#include <AdventOfCode2019/Day05-SunnyWithAsteroids/IntcodeInterpreter.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <Eigen/Dense>

#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day11
{

using AdventOfCode::Year2019::Day05::IntcodeInterpreter;

using Coordinates = std::pair<int, int>;

using Vector2D = Eigen::Matrix<int, 2, 1>;

enum class PaintColor
{
    BLACK = 0,
    WHITE = 1,
};

const char BLACK_CHAR = ' ';
const char WHITE_CHAR = '.';

using CoordinatesToColor = std::unordered_map<Coordinates, PaintColor, boost::hash<Coordinates>>;

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class HullPaintingRobot
{
public:
    HullPaintingRobot(IntcodeInterpreter interpreter);
    HullPaintingRobot(IntcodeInterpreter interpreter, CoordinatesToColor initialCoordinatesToColor);

    void paint();

    unsigned getNumPanelsPaintedAtLeastOnce() const;
    std::string getRegistrationIdentifier() const;

private:
    IntcodeInterpreter m_interpreter;

    Coordinates m_currentCoordinates;
    Direction m_direction;

    CoordinatesToColor m_coordinatesToColor;

    void moveForward();
    void turnLeft();
    void turnRight();

    PaintColor getCurrentColor() const;
    std::pair<Vector2D, Vector2D> getBoundingBox() const;
};

}
}
}
