#include "HullPaintingRobot.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day11
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;
using AdventOfCode::Year2019::Day05::IntcodeProgramExecutionState;

HullPaintingRobot::HullPaintingRobot(IntcodeInterpreter interpreter)
    : HullPaintingRobot(interpreter, {})
{

}

HullPaintingRobot::HullPaintingRobot(IntcodeInterpreter interpreter, CoordinatesToColor initialCoordinatesToColor)
    : m_interpreter{std::move(interpreter)}
    , m_currentCoordinates{0, 0}
    , m_direction{Direction::UP}
    , m_coordinatesToColor{std::move(initialCoordinatesToColor)}
{

}

void HullPaintingRobot::paint()
{
    while (m_interpreter.getExecutionState() != IntcodeProgramExecutionState::TERMINATED)
    {
        m_interpreter.addInput(static_cast<IntcodeNumberType>(getCurrentColor()));
        m_interpreter.execute();

        const auto& outputs = m_interpreter.getOutputs();
        assert(outputs.size() == 0 || outputs.size() == 2);

        if (outputs.size() == 2)
        {
            m_coordinatesToColor[m_currentCoordinates] = static_cast<PaintColor>(outputs.front());

            if (outputs.back() == 0)
            {
                turnLeft();
            }
            else
            {
                turnRight();
            }

            moveForward();
            m_interpreter.clearOutputs();
        }
    }
}

unsigned HullPaintingRobot::getNumPanelsPaintedAtLeastOnce() const
{
    return m_coordinatesToColor.size();
}

std::string HullPaintingRobot::getRegistrationIdentifier() const
{
    std::pair<Vector2D, Vector2D> boundingBox = getBoundingBox();

    const Vector2D& offset = boundingBox.first;
    const Vector2D& size = boundingBox.second;

    const int width = size[0];
    const int height = size[1];

    std::vector<std::string> serializedLines(height, std::string(width, BLACK_CHAR));

    for (const auto& coordinatesAndColor : m_coordinatesToColor)
    {
        if (coordinatesAndColor.second == PaintColor::WHITE)
        {
            const Coordinates& coordinates = coordinatesAndColor.first;
            Vector2D positionVector{coordinates.first, coordinates.second};
            Vector2D positionRelativeToBoundingBox{positionVector - offset};

            const int posX = positionRelativeToBoundingBox[0];
            const int posY = positionRelativeToBoundingBox[1];

            serializedLines.at(posY).at(posX) = WHITE_CHAR;
        }
    }

    std::reverse(serializedLines.begin(), serializedLines.end());

    return boost::algorithm::join(serializedLines, "\n");
}

void HullPaintingRobot::moveForward()
{
    switch (m_direction)
    {
        case Direction::LEFT:
            m_currentCoordinates.first -= 1;
            break;
        case Direction::RIGHT:
            m_currentCoordinates.first += 1;
            break;
        case Direction::UP:
            m_currentCoordinates.second += 1;
            break;
        case Direction::DOWN:
            m_currentCoordinates.second -= 1;
            break;
        default:
            throw std::runtime_error("Invalid direction");
    }
}

void HullPaintingRobot::turnLeft()
{
    switch (m_direction)
    {
        case Direction::LEFT:
            m_direction = Direction::DOWN;
            break;
        case Direction::RIGHT:
            m_direction = Direction::UP;
            break;
        case Direction::UP:
            m_direction = Direction::LEFT;
            break;
        case Direction::DOWN:
            m_direction = Direction::RIGHT;
            break;
        default:
            throw std::runtime_error("Invalid direction");
    }
}

void HullPaintingRobot::turnRight()
{
    for (int i = 1; i <= 3; ++i)
    {
        turnLeft();
    }
}

PaintColor HullPaintingRobot::getCurrentColor() const
{
    const auto currentCoordinatesAndColorIter = m_coordinatesToColor.find(m_currentCoordinates);
    if (currentCoordinatesAndColorIter == m_coordinatesToColor.cend())
    {
        return PaintColor::BLACK;
    }
    return currentCoordinatesAndColorIter->second;
}

std::pair<Vector2D, Vector2D> HullPaintingRobot::getBoundingBox() const
{
    auto minmaxXCoordinatesIterPair = std::minmax_element(m_coordinatesToColor.cbegin(), m_coordinatesToColor.cend(), [](const auto& lhs, const auto& rhs)
                                                            {
                                                                const auto& lhsCoords = lhs.first;
                                                                const auto& rhsCoords = rhs.first;
                                                                return lhsCoords.first < rhsCoords.first;
                                                            });

    const auto& minXCoordsAndColor = minmaxXCoordinatesIterPair.first;
    const auto& maxXCoordsAndColor = minmaxXCoordinatesIterPair.second;
    const auto& minXCoords = minXCoordsAndColor->first;
    const auto& maxXCoords = maxXCoordsAndColor->first;
    const int minX = minXCoords.first;
    const int maxX = maxXCoords.first;

    auto minmaxYCoordinatesIterPair = std::minmax_element(m_coordinatesToColor.cbegin(), m_coordinatesToColor.cend(), [](const auto& lhs, const auto& rhs)
                                                            {
                                                                const auto& lhsCoords = lhs.first;
                                                                const auto& rhsCoords = rhs.first;
                                                                return lhsCoords.second < rhsCoords.second;
                                                            });

    const auto& minYCoordsAndColor = minmaxYCoordinatesIterPair.first;
    const auto& maxYCoordsAndColor = minmaxYCoordinatesIterPair.second;
    const auto& minYCoords = minYCoordsAndColor->first;
    const auto& maxYCoords = maxYCoordsAndColor->first;
    const int minY = minYCoords.second;
    const int maxY = maxYCoords.second;

    return std::make_pair(Vector2D{minX, minY}, Vector2D{maxX - minX + 1, maxY - minY + 1});
}

}
}
}
