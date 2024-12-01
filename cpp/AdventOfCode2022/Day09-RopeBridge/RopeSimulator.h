#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>
#include <Eigen/dense>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day09
{

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct Motion
{
    Direction direction;
    unsigned magnitude;
};

using Vector2D = Eigen::Vector2i;

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

class RopeSimulator
{
public:
    RopeSimulator(std::vector<Motion> motions, unsigned numKnots);

    void simulate();

    int getNumPositionsVisitedByTail() const;

private:
    std::vector<Motion> m_motions;

    std::vector<Vector2D> m_knotPositions;
    std::unordered_set<Vector2D, Vector2DHash> m_positionsVisitedByTail;

    void simulateMotion(const Motion& motion);
    void simulateSingleStep(Direction direction);
    void moveHeadBySingleStepTowardsDirection(Direction direction);
    void adjustKnotsBehindHead();

    static void adjustTailAccordingToHead(Vector2D& tailPosition, const Vector2D& headPosition);
    static Vector2D getSingleStepMotionVector(Direction direction);
};

}
}
}
