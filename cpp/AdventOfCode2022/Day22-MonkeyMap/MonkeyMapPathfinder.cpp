#include "MonkeyMapPathfinder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int PASSWORD_ROW_MULTIPLIER = 1000;
const int PASSWORD_COLUMN_MULTIPLIER = 4;
const char VOID_TILE = ' ';
const char OPEN_TILE = '.';
const char WALL_TILE = '#';

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day22
{

MonkeyMapPathfinder::MonkeyMapPathfinder(MonkeyMap monkeyMap, Instructions instructions)
    : m_monkeyMap{std::move(monkeyMap)}
    , m_width{m_monkeyMap.at(0).size()}
    , m_height{m_monkeyMap.size()}
    , m_instructions{std::move(instructions)}
    , m_currentDirection{RIGHT_DIRECTION}
{
    for (int i = 0; i < m_width; ++i)
    {
        if (m_monkeyMap.at(0).at(i) == OPEN_TILE)
        {
            m_currentPosition = {i, 0};
            break;
        }
    }

    m_leftRotationMatrix2D <<
        0, -1,
        1, 0;
}

void MonkeyMapPathfinder::executeInstructions()
{
    for (const auto& instruction : m_instructions)
    {
        moveForward(instruction.numSteps);
        rotate(instruction.rotationDirection);
    }
}

int MonkeyMapPathfinder::getFinalPassword() const
{
    int directionAddend = 0;

    auto currentDirectionCopy{m_currentDirection};
    while (currentDirectionCopy != RIGHT_DIRECTION)
    {
        currentDirectionCopy *= m_leftRotationMatrix2D;
        ++directionAddend;
    }

    return (m_currentPosition.y() + 1) * PASSWORD_ROW_MULTIPLIER + (m_currentPosition.x() + 1) * PASSWORD_COLUMN_MULTIPLIER + directionAddend;
}

std::pair<MonkeyMapPathfinder::Vector2D, MonkeyMapPathfinder::Vector2D> MonkeyMapPathfinder::getNextPositionAndDirection() const
{
    Vector2D nextPosition = m_currentPosition;
    do
    {
        nextPosition += m_currentDirection;

        nextPosition.y() = (nextPosition.y() + m_height) % m_height;
        nextPosition.x() = (nextPosition.x() + m_width) % m_width;
    } while (getTileAt(nextPosition) == VOID_TILE);

    return {nextPosition, m_currentDirection};
}

char MonkeyMapPathfinder::getTileAt(const Vector2D& position) const
{
    if (position.x() < 0 || position.x() >= m_width || position.y() < 0 || position.y() >= m_height)
    {
        return VOID_TILE;
    }

    return m_monkeyMap.at(position.y()).at(position.x());
}

void MonkeyMapPathfinder::moveForward(unsigned numSteps)
{
    for (unsigned step = 0; step < numSteps; ++step)
    {
        moveForwardOnce();
    }
}

void MonkeyMapPathfinder::rotate(char direction)
{
    if (direction == 'L')
    {
        rotateLeft();
    }
    else if (direction == 'R')
    {
        rotateRight();
    }
}

void MonkeyMapPathfinder::moveForwardOnce()
{
    auto newPositionAndDirection = getNextPositionAndDirection();
    if (getTileAt(newPositionAndDirection.first) == OPEN_TILE)
    {
        m_currentPosition = newPositionAndDirection.first;
        m_currentDirection = newPositionAndDirection.second;
    }
}

void MonkeyMapPathfinder::rotateLeft()
{
    m_currentDirection *= m_leftRotationMatrix2D;
}

void MonkeyMapPathfinder::rotateRight()
{
    rotateLeft();
    rotateLeft();
    rotateLeft();
}

MonkeyMapCubePathfinder::MonkeyMapCubePathfinder(MonkeyMap monkeyMap, Instructions instructions, unsigned cubeSize)
    : MonkeyMapPathfinder{std::move(monkeyMap), std::move(instructions)}
    , m_cubeSize{cubeSize}
{

}

void MonkeyMapCubePathfinder::fold()
{
    CubeFace initialCubeFace{{0, 0, 0}, INITIAL_FACE_NORMAL, Matrix3D::Identity()};

    std::queue<Vector2D> bfsQueue;
    bfsQueue.push(m_currentPosition);
    m_mapPositionToCubeFace.emplace(m_currentPosition, initialCubeFace);
    m_cubeFaceToMapPosition.emplace(initialCubeFace, m_currentPosition);

    while (!bfsQueue.empty())
    {
        Vector2D currentPosition = bfsQueue.front();
        bfsQueue.pop();

        std::vector<std::pair<Vector2D, CubeFace>> neighborMapPositionsAndNeighboringCubeFaces = getNeighborMapPositionsAndNeighboringCubeFaces(currentPosition);

        for (const auto& neighborMapPositionAndNeighboringCubeFace : neighborMapPositionsAndNeighboringCubeFaces)
        {
            if (m_mapPositionToCubeFace.emplace(neighborMapPositionAndNeighboringCubeFace.first, neighborMapPositionAndNeighboringCubeFace.second).second)
            {
                m_cubeFaceToMapPosition.emplace(neighborMapPositionAndNeighboringCubeFace.second, neighborMapPositionAndNeighboringCubeFace.first);
                bfsQueue.push(neighborMapPositionAndNeighboringCubeFace.first);
            }
        }
    }
}

std::pair<MonkeyMapCubePathfinder::Vector2D, MonkeyMapCubePathfinder::Vector2D> MonkeyMapCubePathfinder::getNextPositionAndDirection() const
{
    const CubeFace& currentCubeFace = m_mapPositionToCubeFace.at(m_currentPosition);
    const Vector2D nextPositionWithoutWrapping = m_currentPosition + m_currentDirection;

    const CubeFace nextCubeFace = getCubeFaceForMovement(currentCubeFace, m_currentDirection, m_currentPosition, nextPositionWithoutWrapping);

    const Vector2D nextPositionWithWrapping = m_cubeFaceToMapPosition.at(nextCubeFace);
    const Vector2D newDirectionAfterWrapping = getNewDirectionAfterWrapping(nextPositionWithoutWrapping, nextPositionWithWrapping);

    return {nextPositionWithWrapping, newDirectionAfterWrapping};
}

std::vector<std::pair<MonkeyMapCubePathfinder::Vector2D, MonkeyMapCubePathfinder::CubeFace>> MonkeyMapCubePathfinder::getNeighborMapPositionsAndNeighboringCubeFaces(const Vector2D& currentPosition) const
{
    std::vector<std::pair<Vector2D, CubeFace>> neighborMapPositionsAndNeighboringCubeFaces;

    const std::vector<Vector2D> directionVectors =
    {
        RIGHT_DIRECTION,
        LEFT_DIRECTION,
        DOWN_DIRECTION
    };

    for (const auto& directionVector : directionVectors)
    {
        auto neighboringCubeFaceAndMapPosition = getNeighborMapPositionAndCubeFace(currentPosition, directionVector);
        if (neighboringCubeFaceAndMapPosition)
        {
            neighborMapPositionsAndNeighboringCubeFaces.push_back(std::move(neighboringCubeFaceAndMapPosition.get()));
        }
    }

    return neighborMapPositionsAndNeighboringCubeFaces;
}

boost::optional<std::pair<MonkeyMapCubePathfinder::Vector2D, MonkeyMapCubePathfinder::CubeFace>> MonkeyMapCubePathfinder::getNeighborMapPositionAndCubeFace(const Vector2D& currentPosition, const Vector2D& directionVector) const
{
    const CubeFace& currentCubeFace = m_mapPositionToCubeFace.at(currentPosition);
    Vector2D nextPosition = currentPosition + directionVector;
    if (getTileAt(nextPosition) == VOID_TILE)
    {
        return boost::none;
    }

    CubeFace nextCubeFace = getCubeFaceForMovement(currentCubeFace, directionVector, currentPosition, nextPosition);

    return {{std::move(nextPosition), std::move(nextCubeFace)}};
}

MonkeyMapCubePathfinder::CubeFace MonkeyMapCubePathfinder::getCubeFaceForMovement(const CubeFace& currentCubeFace, const Vector2D& directionVector, const Vector2D& currentPosition, const Vector2D& nextPosition) const
{
    Vector2D mapRegionDelta{getMapRegion(nextPosition.x()) - getMapRegion(currentPosition.x()), getMapRegion(nextPosition.y()) - getMapRegion(currentPosition.y())};

    if (mapRegionDelta.sum() == 0)
    {
        const Vector3D directionVectorInCubeFaceCoordinateSystem = transformVectorIntoCubeFaceCoordinateSystem(currentCubeFace, {directionVector.x(), directionVector.y(), 0});
        return CubeFace{currentCubeFace.cubePosition + directionVectorInCubeFaceCoordinateSystem, currentCubeFace.surfaceNormal, currentCubeFace.transformationMatrixToOwnCoordinateSystem};
    }
    // Moving to a different face of the large cube
    else
    {
        // Map region delta (transformed to the coordinate system of the current cube) is going to be the normal vector of the new cube face
        const Vector3D mapRegionDeltaInCubeFaceCoordinateSystem = transformVectorIntoCubeFaceCoordinateSystem(currentCubeFace, {mapRegionDelta.x(), mapRegionDelta.y(), 0});
        const Matrix3D additionalTransformationMatrix = getRotationMatrixForSingle90DegreeRotation(currentCubeFace.surfaceNormal, mapRegionDeltaInCubeFaceCoordinateSystem);
        return CubeFace{currentCubeFace.cubePosition, mapRegionDeltaInCubeFaceCoordinateSystem, currentCubeFace.transformationMatrixToOwnCoordinateSystem * additionalTransformationMatrix};
    }
}

MonkeyMapCubePathfinder::Vector3D MonkeyMapCubePathfinder::transformVectorIntoCubeFaceCoordinateSystem(const CubeFace& cubeFace, const Vector3D vector) const
{
    return vector * cubeFace.transformationMatrixToOwnCoordinateSystem;
}

MonkeyMapCubePathfinder::Matrix3D MonkeyMapCubePathfinder::getRotationMatrixForSingle90DegreeRotation(const Vector3D& originalVector, const Vector3D& expectedResult) const
{
    if (originalVector == expectedResult)
    {
        return Matrix3D::Identity();
    }

    Matrix3D firstRotationMatrix;
    firstRotationMatrix <<
        0, 1, 0,
        -1, 0, 0,
        0, 0, 1;

    Matrix3D secondRotationMatrix;
    secondRotationMatrix <<
        1, 0, 0,
        0, 0, 1,
        0, -1, 0;

    Matrix3D thirdRotationMatrix;
    thirdRotationMatrix <<
        0, 0, -1,
        0, 1, 0,
        1, 0, 0;

    std::vector<Matrix3D> rotationMatrices{firstRotationMatrix, secondRotationMatrix, thirdRotationMatrix};
    std::vector<Matrix3D> transformationMatrixCandidates;

    for (const auto& rotationMatrix : rotationMatrices)
    {
        // Apply once
        Matrix3D transformationMatrixCandidate = rotationMatrix;
        transformationMatrixCandidates.push_back(transformationMatrixCandidate);

        // Apply three times in total
        transformationMatrixCandidate *= rotationMatrix;
        transformationMatrixCandidate *= rotationMatrix;
        transformationMatrixCandidates.push_back(transformationMatrixCandidate);
    }

    for (const auto& transformationMatrixCandidate : transformationMatrixCandidates)
    {
        if (originalVector * transformationMatrixCandidate == expectedResult)
        {
            return transformationMatrixCandidate;
        }
    }

    throw std::runtime_error("Could not find rotation matrix");
}

int MonkeyMapCubePathfinder::getMapRegion(int coordinate) const
{
    return (coordinate + m_cubeSize) / m_cubeSize - 1;
}

MonkeyMapCubePathfinder::Vector2D MonkeyMapCubePathfinder::getRelativePositionInsideMapRegion(const Vector2D absolutePosition) const
{
    return {(absolutePosition.x() + m_cubeSize) % m_cubeSize, (absolutePosition.y() + m_cubeSize) % m_cubeSize};
}

MonkeyMapCubePathfinder::Vector2D MonkeyMapCubePathfinder::getNewDirectionAfterWrapping(const Vector2D& nextPositionWithoutWrapping, const Vector2D& nextPositionWithWrapping) const
{
    const Vector2D relativePositionWithoutWrapping = getRelativePositionInsideMapRegion(nextPositionWithoutWrapping);
    const Vector2D relativePositionWithWrapping = getRelativePositionInsideMapRegion(nextPositionWithWrapping);

    Vector2D rotatedRelativePositionWithoutWrapping{relativePositionWithoutWrapping};
    Vector2D updatedDirection{m_currentDirection};

    while (rotatedRelativePositionWithoutWrapping != relativePositionWithWrapping)
    {
        updatedDirection *= m_leftRotationMatrix2D;

        rotatedRelativePositionWithoutWrapping.x() = m_cubeSize - 1 - rotatedRelativePositionWithoutWrapping.x();
        std::swap(rotatedRelativePositionWithoutWrapping.x(), rotatedRelativePositionWithoutWrapping.y());
    }

    return updatedDirection;
}

}
}
}
