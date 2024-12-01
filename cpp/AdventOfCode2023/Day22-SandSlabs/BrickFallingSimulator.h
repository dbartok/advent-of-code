#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>
#include <Eigen/dense>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day22
{

using Vector3D = Eigen::Vector3i;

struct Vector3DHash
{
    size_t operator()(const Vector3D& vec) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, vec.x());
        boost::hash_combine(seed, vec.y());
        boost::hash_combine(seed, vec.z());

        return seed;
    }
};

class Brick
{
public:
    Brick(Vector3D startPosition, Vector3D endPosition);

    void moveDown();
    void moveUp();

    int getLowestZCoordinate() const;
    std::vector<Vector3D> getAllOccupiedPositions() const;

    bool operator==(const Brick& other) const;
    bool operator!=(const Brick& other) const;

private:
    Vector3D m_startPosition;
    Vector3D m_endPosition;
};

class BrickFallingSimulator
{
public:
    BrickFallingSimulator(std::vector<Brick> bricks);

    // Returns the number of bricks moved during the settling process
    int settle();

    const std::vector<Brick>& getBricks() const;

private:
    std::vector<Brick> m_bricks;
    std::unordered_set<Vector3D, Vector3DHash> m_occupiedPositions;

    // Returns true if the brick has moved as part of settling
    bool settleBrick(Brick& brick);
    void eraseBrickFromOccupiedPositions(const Brick& brick);
    void insertBrickIntoOccupiedPositions(const Brick& brick);

    bool isBrickColliding(const Brick& brick) const;
};

}
}
}
