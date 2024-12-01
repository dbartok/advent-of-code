#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>
#include <boost/functional/hash.hpp>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day05
{

using Vector2D = Eigen::Matrix<int, 2, 1>;

struct Vector2DHash
{
    size_t operator()(const Vector2D& vec) const
    {
        size_t seed = 0;

        boost::hash_combine(seed, vec.x());
        boost::hash_combine(seed, vec.y());

        return seed;
    }
};

class LineSegment
{
public:
    LineSegment(Vector2D start, Vector2D end);

    bool isAxisParallel() const;
    std::vector<Vector2D> getCoveredPoints() const;

private:
    Vector2D m_start;
    Vector2D m_end;
};

}
}
}
