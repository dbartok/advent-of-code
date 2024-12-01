#include "Day09-RopeBridge.h"

#include "RopeSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

unsigned SHORT_ROPE_NUM_KNOTS = 2;
unsigned LONG_ROPE_NUM_KNOTS = 10;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day09
{

Direction parseDirectionChar(char directionChar)
{
    switch (directionChar)
    {
        case 'U':
            return Direction::UP;
        case 'D':
            return Direction::DOWN;
        case 'L':
            return Direction::LEFT;
        case 'R':
            return Direction::RIGHT;
        default:
            throw std::runtime_error("Error parsing direction char: " + std::string{directionChar});
    }
}

Motion parseMotionLine(const std::string& motionLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, motionLine, boost::is_any_of(" "));

    const Direction direction = parseDirectionChar(tokens.at(0).front());
    const unsigned magnitude = std::stoi(tokens.at(1));

    return Motion{direction, magnitude};
}

std::vector<Motion> parseMotionLines(const std::vector<std::string>& motionLines)
{
    std::vector<Motion> motions;

    for (const auto& motionLine : motionLines)
    {
        Motion motion = parseMotionLine(motionLine);
        motions.push_back(std::move(motion));
    }

    return motions;
}


int numPositionsVisitedByTail(const std::vector<std::string>& motionLines)
{
    std::vector<Motion> motions = parseMotionLines(motionLines);

    RopeSimulator ropeSimulator{std::move(motions), SHORT_ROPE_NUM_KNOTS};

    ropeSimulator.simulate();

    return ropeSimulator.getNumPositionsVisitedByTail();
}

int numPositionsVisitedByTailWithLongerRope(const std::vector<std::string>& motionLines)
{
    std::vector<Motion> motions = parseMotionLines(motionLines);

    RopeSimulator ropeSimulator{std::move(motions), LONG_ROPE_NUM_KNOTS};

    ropeSimulator.simulate();

    return ropeSimulator.getNumPositionsVisitedByTail();
}

}
}
}