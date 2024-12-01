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
namespace Day13
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;
using AdventOfCode::Year2019::Day05::IntcodeInterpreter;

using Coordinates = std::pair<int, int>;

enum class TileID
{
    EMPTY = 0,
    WALL = 1,
    BLOCK = 2,
    PADDLE = 3,
    BALL = 4,
};

using CoordinatesToTileID = std::unordered_map<Coordinates, TileID, boost::hash<Coordinates>>;

class ArcadeCabinet
{
public:
    ArcadeCabinet(IntcodeInterpreter interpreter);

    void play();

    unsigned getNumBlockTiles() const;
    int getScore() const;

private:
    IntcodeInterpreter m_interpreter;

    CoordinatesToTileID m_coordinatesToTileID;

    Coordinates m_ballPos;
    Coordinates m_paddlePos;

    int m_score;

    void updateDisplay(const std::vector<IntcodeNumberType>& outputs);
    void updatePixel(const Coordinates& coordinates, IntcodeNumberType value);
    int getNextInput() const;
};

}
}
}
