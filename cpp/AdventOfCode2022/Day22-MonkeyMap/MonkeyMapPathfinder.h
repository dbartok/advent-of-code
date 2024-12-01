#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/dense>
#include <boost/optional.hpp>
#include <boost/functional/hash.hpp>

#include <vector>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day22
{

using MonkeyMap = std::vector<std::string>;

struct Instruction
{
    unsigned numSteps = 0;
    char rotationDirection = '\0';
};

using Instructions = std::vector<Instruction>;

class MonkeyMapPathfinder
{
public:
    MonkeyMapPathfinder(MonkeyMap monkeyMap, Instructions instructions);

    void executeInstructions();

    int getFinalPassword() const;

protected:
    // x points right, y points down, z points towards the screen
    using Vector2D = Eigen::RowVector2i;

    struct Vector2DHash
    {
        size_t operator()(const Vector2D& vec) const
        {
            std::size_t seed = 0;

            boost::hash_combine(seed, vec.x());
            boost::hash_combine(seed, vec.y());

            return seed;
        }
    };

    using Matrix2D = Eigen::Matrix2i;
    using Matrix3D = Eigen::Matrix3i;

    const Vector2D RIGHT_DIRECTION{1, 0};
    const Vector2D LEFT_DIRECTION{-1, 0};
    const Vector2D DOWN_DIRECTION{0, 1};

    Matrix2D m_leftRotationMatrix2D;

    MonkeyMap m_monkeyMap;
    size_t m_width;
    size_t m_height;

    Vector2D m_currentPosition;
    Vector2D m_currentDirection;

    virtual std::pair<Vector2D, Vector2D> getNextPositionAndDirection() const;
    char getTileAt(const Vector2D& position) const;

private:
    Instructions m_instructions;

    void moveForward(unsigned numSteps);
    void rotate(char direction);
    void moveForwardOnce();
    void rotateLeft();
    void rotateRight();
};

class MonkeyMapCubePathfinder : public MonkeyMapPathfinder
{
public:
    MonkeyMapCubePathfinder(MonkeyMap monkeyMap, Instructions instructions, unsigned cubeSize);

    void fold();

private:
    using Vector3D = Eigen::RowVector3i;

    const Vector3D INITIAL_FACE_NORMAL{0, 0, -1};

    struct CubeFace
    {
        Vector3D cubePosition;
        Vector3D surfaceNormal;
        Matrix3D transformationMatrixToOwnCoordinateSystem;

        bool operator==(const CubeFace& other) const
        {
            return cubePosition == other.cubePosition && surfaceNormal == other.surfaceNormal;
        }
    };

    struct CubeFaceHash
    {
        size_t operator()(const CubeFace& cubeFace) const
        {
            std::size_t seed = 0;

            boost::hash_combine(seed, cubeFace.cubePosition.x());
            boost::hash_combine(seed, cubeFace.cubePosition.y());
            boost::hash_combine(seed, cubeFace.cubePosition.z());
            boost::hash_combine(seed, cubeFace.surfaceNormal.x());
            boost::hash_combine(seed, cubeFace.surfaceNormal.y());
            boost::hash_combine(seed, cubeFace.surfaceNormal.z());

            return seed;
        }
    };

    unsigned m_cubeSize;
    std::unordered_map<Vector2D, CubeFace, Vector2DHash> m_mapPositionToCubeFace;
    std::unordered_map<CubeFace, Vector2D, CubeFaceHash> m_cubeFaceToMapPosition;

    std::pair<Vector2D, Vector2D> getNextPositionAndDirection() const override;

    std::vector<std::pair<Vector2D, CubeFace>> getNeighborMapPositionsAndNeighboringCubeFaces(const Vector2D& currentPosition) const;

    boost::optional<std::pair<Vector2D, CubeFace>> getNeighborMapPositionAndCubeFace(const Vector2D& currentPosition, const Vector2D& directionVector) const;
    CubeFace getCubeFaceForMovement(const CubeFace& currentCubeFace, const Vector2D& directionVector, const Vector2D& currentPosition, const Vector2D& nextPosition) const;
    Vector3D transformVectorIntoCubeFaceCoordinateSystem(const CubeFace& cubeFace, const Vector3D vector) const;
    Matrix3D getRotationMatrixForSingle90DegreeRotation(const Vector3D& originalVector, const Vector3D& expectedResult) const;
    int getMapRegion(int coordinate) const;
    Vector2D getRelativePositionInsideMapRegion(const Vector2D absolutePosition) const;
    Vector2D getNewDirectionAfterWrapping(const Vector2D& nextPositionWithoutWrapping, const Vector2D& nextPositionWithWrapping) const;
};

}
}
}
