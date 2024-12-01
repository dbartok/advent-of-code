#include "PipeDiagramTraverser.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cctype>
#include <cassert>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day19
{

const std::array<PipeDiagramTraverser::Direction, 4> PipeDiagramTraverser::ALL_DIRECTIONS{Direction::LEFT, Direction::RIGHT, Direction::UP, Direction::DOWN};

PipeDiagramTraverser::PipeDiagramTraverser(std::vector<std::string> pipeDiagramLines) noexcept
    : m_pipeDiagramLines{std::move(pipeDiagramLines)}
    , m_currentCoords{}
    , m_currentDirection{Direction::DOWN}
    , m_lettersVisitedSequence{}
    , m_numStepsTaken{0}
{

}

void PipeDiagramTraverser::traverse()
{
    if (!isDiagramRectangle())
    {
        throw std::runtime_error("Traversal only available for rectangular diagrams.");
    }

    if (m_pipeDiagramLines.empty())
    {
        return;
    }

    resetToStartingCoords();

    while (true)
    {
        if (!areCoordsInBounds(m_currentCoords))
        {
            break;
        }

        const char currentChar = m_pipeDiagramLines[m_currentCoords.second][m_currentCoords.first];

        if (currentChar == ' ')
        {
            break;
        }

        ++m_numStepsTaken;

        if (isPath(currentChar))
        {
            if (std::isupper(currentChar))
            {
                m_lettersVisitedSequence += currentChar;
            }
        }
        else if (currentChar == '+')
        {
            const bool ableToSwitch = switchDirection();
            if (!ableToSwitch)
            {
                break;
            }
        }
        else
        {
            throw std::runtime_error("Unknown character encountered.");
        }

        stepInCurrentDirection();
    }

}

std::string PipeDiagramTraverser::getLettersVisitedSequence() const
{
    return m_lettersVisitedSequence;
}

unsigned PipeDiagramTraverser::getNumStepsTaken() const noexcept
{
    return m_numStepsTaken;
}

bool PipeDiagramTraverser::isPath(char currentChar) noexcept
{
    return currentChar == '|' || currentChar == '-' || std::isupper(currentChar);
}

void PipeDiagramTraverser::resetToStartingCoords()
{
    const auto& firstLine = m_pipeDiagramLines.front();
    const auto pathIter = std::find_if(firstLine.cbegin(), firstLine.cend(), [](char c) noexcept { return PipeDiagramTraverser::isPath(c); });

    if (pathIter == firstLine.cend())
    {
        throw std::runtime_error("No starting coordinates found.");
    }

    m_currentCoords = std::make_pair(pathIter - firstLine.cbegin(), 0);
}

bool PipeDiagramTraverser::switchDirection()
{
    for (auto direction : ALL_DIRECTIONS)
    {
        if (areOppositeDirections(m_currentDirection, direction))
        {
            continue;
        }

        const Coordinates coordsInDirection = neighborCoords(direction);
        if (areCoordsInBounds(coordsInDirection) && isPath(m_pipeDiagramLines[coordsInDirection.second][coordsInDirection.first]))
        {
            m_currentDirection = direction;
            return true;
        }
    }

    return false;
}

void PipeDiagramTraverser::stepInCurrentDirection()
{
    m_currentCoords = neighborCoords(m_currentDirection);
}

bool PipeDiagramTraverser::areCoordsInBounds(Coordinates coords) const
{
    if (coords.first < 0)
    {
        return false;
    }

    if (coords.first > m_pipeDiagramLines.front().size() - 1)
    {
        return false;
    }

    if (coords.second < 0)
    {
        return false;
    }

    if (coords.second > m_pipeDiagramLines.size() - 1)
    {
        return false;
    }

    return true;
}

PipeDiagramTraverser::Coordinates PipeDiagramTraverser::neighborCoords(Direction direction)
{
    if (direction == Direction::LEFT)
    {
        return std::make_pair(m_currentCoords.first - 1, m_currentCoords.second);
    }
    else if (direction == Direction::RIGHT)
    {
        return std::make_pair(m_currentCoords.first + 1, m_currentCoords.second);
    }
    else if (direction == Direction::UP)
    {
        return std::make_pair(m_currentCoords.first, m_currentCoords.second - 1);
    }
    else if (direction == Direction::DOWN)
    {
        return std::make_pair(m_currentCoords.first, m_currentCoords.second + 1);
    }
    else
    {
        throw std::runtime_error("Unknown direction.");
    }
}

bool PipeDiagramTraverser::isDiagramRectangle() const
{
    return Utils::allElementsEqual(m_pipeDiagramLines.cbegin(), m_pipeDiagramLines.cend(), [](const auto& lhs, const auto& rhs) noexcept
                                   {
                                       return lhs.size() == rhs.size();
                                   });
}

bool PipeDiagramTraverser::areOppositeDirections(Direction d1, Direction d2)
{
    if (d1 == Direction::LEFT)
    {
        return d2 == Direction::RIGHT;
    }
    else if (d1 == Direction::RIGHT)
    {
        return d2 == Direction::LEFT;
    }
    else if (d1 == Direction::UP)
    {
        return d2 == Direction::DOWN;
    }
    else if (d1 == Direction::DOWN)
    {
        return d2 == Direction::UP;
    }
    else
    {
        throw std::runtime_error("Unknown direction.");
    }
}

}
}
}
