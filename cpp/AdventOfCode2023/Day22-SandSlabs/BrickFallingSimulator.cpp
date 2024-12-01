#include "BrickFallingSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day22
{

Brick::Brick(Vector3D startPosition, Vector3D endPosition)
    : m_startPosition{std::move(startPosition)}
    , m_endPosition{std::move(endPosition)}
{

}

void Brick::moveDown()
{
    m_startPosition.z() -= 1;
    m_endPosition.z() -= 1;
}

void Brick::moveUp()
{
    m_startPosition.z() += 1;
    m_endPosition.z() += 1;
}

int Brick::getLowestZCoordinate() const
{
    return std::min(m_startPosition.z(), m_endPosition.z());
}

std::vector<Vector3D> Brick::getAllOccupiedPositions() const
{
    Vector3D difference = m_endPosition - m_startPosition;
    difference.normalize();

    std::vector<Vector3D> allOccupiedPositions;

    for (Vector3D position = m_startPosition; position != m_endPosition; position += difference)
    {
        allOccupiedPositions.push_back(position);
    }

    allOccupiedPositions.push_back(m_endPosition);

    return allOccupiedPositions;
}

bool Brick::operator==(const Brick& other) const
{
    return m_startPosition == other.m_startPosition && m_endPosition == other.m_endPosition;
}

bool Brick::operator!=(const Brick& other) const
{
    return !(*this == other);
}

BrickFallingSimulator::BrickFallingSimulator(std::vector<Brick> bricks)
    : m_bricks{std::move(bricks)}
{
    for (const auto& brick : m_bricks)
    {
        for (const auto& position : brick.getAllOccupiedPositions())
        {
            m_occupiedPositions.insert(position);
        }
    }
}

int BrickFallingSimulator::settle()
{
    std::sort(m_bricks.begin(), m_bricks.end(), [](const auto& lhs, const auto& rhs)
                {
                    return lhs.getLowestZCoordinate() < rhs.getLowestZCoordinate();
                });

    int numBricksMoved = 0;

    for (auto& brick : m_bricks)
    {
        if (settleBrick(brick))
        {
            ++numBricksMoved;
        }
    }

    return numBricksMoved;
}

const std::vector<Brick>& BrickFallingSimulator::getBricks() const
{
    return m_bricks;
}

bool BrickFallingSimulator::settleBrick(Brick& brick)
{
    eraseBrickFromOccupiedPositions(brick);

    int numDownwardsMovements = 0;

    while (!isBrickColliding(brick))
    {
        brick.moveDown();
        ++numDownwardsMovements;
    }

    // We deliberately moved the brick one step too far to find the collision, so the settled position is actually the previous position
    brick.moveUp();
    --numDownwardsMovements;

    insertBrickIntoOccupiedPositions(brick);

    return numDownwardsMovements > 0;
}

void BrickFallingSimulator::eraseBrickFromOccupiedPositions(const Brick& brick)
{
    for (const Vector3D& position : brick.getAllOccupiedPositions())
    {
        m_occupiedPositions.erase(position);
    }
}

void BrickFallingSimulator::insertBrickIntoOccupiedPositions(const Brick& brick)
{
    for (const Vector3D& position : brick.getAllOccupiedPositions())
    {
        m_occupiedPositions.insert(position);
    }
}

bool BrickFallingSimulator::isBrickColliding(const Brick& brick) const
{
    // Check for collision with floor
    if (brick.getLowestZCoordinate() < 1)
    {
        return true;
    }

    // Check for collision with another brick
    std::vector<Vector3D> allOccupiedPositions = brick.getAllOccupiedPositions();
    return std::any_of(allOccupiedPositions.cbegin(), allOccupiedPositions.cend(), [this](const auto& pos)
                        {
                            return this->m_occupiedPositions.find(pos) != this->m_occupiedPositions.cend();
                        });
}

}
}
}
