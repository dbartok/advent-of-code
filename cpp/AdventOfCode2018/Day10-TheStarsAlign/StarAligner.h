#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>

#include<vector>
#include<string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day10
{

using CoordinateNumericType = int;
using Vector2D = Eigen::Matrix<CoordinateNumericType, 2, 1>;

struct Starlight
{
    Vector2D position;
    Vector2D velocity;

    Starlight(Vector2D position, Vector2D velocity) noexcept;
};

struct StarBoundingBox
{
    Vector2D offset;
    Vector2D size;

    StarBoundingBox(Vector2D offset, Vector2D size) noexcept;
};

class StarAligner
{
public:
    StarAligner(std::vector<Starlight> starlights) noexcept;

    void align();

    std::string getSerializedMessage() const;
    unsigned getTimeUnitsElapsed() const noexcept;

private:
    std::vector<Starlight> m_starlights;
    unsigned m_timeElapsed;

    void stepOneTimeUnit();
    void rewindOneTimeUnit();

    StarBoundingBox getBoundingBox() const;
};

}
}
}
