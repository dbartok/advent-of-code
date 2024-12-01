#include "RopeSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day09
{

RopeSimulator::RopeSimulator(std::vector<Motion> motions, unsigned numKnots)
    : m_motions{std::move(motions)}
{
    for (unsigned iteration = 0; iteration < numKnots; ++iteration)
    {
        m_knotPositions.emplace_back(0, 0);
    }
}

void RopeSimulator::simulate()
{
    for (const auto& motion : m_motions)
    {
        simulateMotion(motion);
    }
}

int RopeSimulator::getNumPositionsVisitedByTail() const
{
    return m_positionsVisitedByTail.size();
}

void RopeSimulator::simulateMotion(const Motion& motion)
{
    for (unsigned iteration = 0; iteration < motion.magnitude; ++iteration)
    {
        simulateSingleStep(motion.direction);
    }
}

void RopeSimulator::simulateSingleStep(Direction direction)
{
    moveHeadBySingleStepTowardsDirection(direction);
    adjustKnotsBehindHead();
    m_positionsVisitedByTail.insert(m_knotPositions.back());
}

void RopeSimulator::moveHeadBySingleStepTowardsDirection(Direction direction)
{
    const Vector2D movementVector = getSingleStepMotionVector(direction);
    m_knotPositions.front() += movementVector;
}

void RopeSimulator::adjustKnotsBehindHead()
{
    for (size_t i = 1; i < m_knotPositions.size(); ++i)
    {
        adjustTailAccordingToHead(m_knotPositions.at(i), m_knotPositions.at(i - 1));
    }
}

void RopeSimulator::adjustTailAccordingToHead(Vector2D& tailPosition, const Vector2D& headPosition)
{
    const Vector2D tailToHeadVector = headPosition - tailPosition;

    if (abs(tailToHeadVector.x()) > 1 || abs(tailToHeadVector.y()) > 1)
    {
        const int adjustmentX = abs(tailToHeadVector.x()) > 0 ? tailToHeadVector.x() / abs(tailToHeadVector.x()) : 0;
        const int adjustmentY = abs(tailToHeadVector.y()) > 0 ? tailToHeadVector.y() / abs(tailToHeadVector.y()) : 0;

        const Vector2D adjustmentVector = Vector2D{adjustmentX, adjustmentY};

        tailPosition += adjustmentVector;
    }
}

Vector2D RopeSimulator::getSingleStepMotionVector(Direction direction)
{
    switch (direction)
    {
        case Direction::UP:
            return Vector2D{0, 1};
        case Direction::DOWN:
            return Vector2D{0, -1};
        case Direction::LEFT:
            return Vector2D{-1, 0};
        case Direction::RIGHT:
            return Vector2D{1, 0};
        default:
            throw std::runtime_error("Invalid direction: " + std::to_string(static_cast<int>(direction)));
    }
}

}
}
}
