#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/dense>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day17
{

using Vector2D = Eigen::Vector2i;

struct TargetArea
{
    Vector2D lowerBoundVector;
    Vector2D upperBoundVector;
};

class ProbeLauncherSimulator
{
public:
    ProbeLauncherSimulator(TargetArea targetArea);

    int getHighestPossibleYPosition() const;
    unsigned getNumDistinctInitialVelocityValues() const;

private:
    TargetArea m_targetArea;

    bool canProbeStopHorizonatallyInsideTargetArea() const;
    int getHighestInitialVelocityY() const;
    bool isWithinTargetAfterAnyStep(const Vector2D& initialVelocityVector) const;
    bool isWithinTarget(const Vector2D& positionVector) const;
};

}
}
}
