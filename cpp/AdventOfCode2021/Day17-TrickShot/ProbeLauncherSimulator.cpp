#include "ProbeLauncherSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day17
{

ProbeLauncherSimulator::ProbeLauncherSimulator(TargetArea targetArea)
    : m_targetArea{std::move(targetArea)}
{

}

int ProbeLauncherSimulator::getHighestPossibleYPosition() const
{
    if (!canProbeStopHorizonatallyInsideTargetArea())
    {
        throw std::runtime_error("Probe horizontal stop condition violated");
    }
    const int highestInitialVelocityY = getHighestInitialVelocityY();
    const int highestPossibleYPosition = highestInitialVelocityY * (highestInitialVelocityY + 1) / 2;
    return highestPossibleYPosition;
}

unsigned ProbeLauncherSimulator::getNumDistinctInitialVelocityValues() const
{
    unsigned numDistinctInitialVelocityValues = 0;

    for (int initialVelocityY = std::min(m_targetArea.lowerBoundVector.y(), 0); initialVelocityY <= getHighestInitialVelocityY(); ++initialVelocityY)
    {
        for (int initialVelocityX = std::min(m_targetArea.lowerBoundVector.x(), 0); initialVelocityX <= std::max(0, m_targetArea.upperBoundVector.x()); ++initialVelocityX)
        {
            if (isWithinTargetAfterAnyStep({initialVelocityX, initialVelocityY}))
            {
                ++numDistinctInitialVelocityValues;
            }
        }
    }

    return numDistinctInitialVelocityValues;
}

bool ProbeLauncherSimulator::canProbeStopHorizonatallyInsideTargetArea() const
{
    int initialVelocityX = sqrt(std::abs(m_targetArea.upperBoundVector.x()));
    while (true)
    {
        const int stopPositionX = initialVelocityX * (initialVelocityX + 1) / 2;
        if (stopPositionX >= m_targetArea.lowerBoundVector.x())
        {
            return stopPositionX <= m_targetArea.upperBoundVector.x();
        }

        ++initialVelocityX;
    }
}

int ProbeLauncherSimulator::getHighestInitialVelocityY() const
{
    // Target is completely beneath the surface
    if (m_targetArea.lowerBoundVector.y() < 0)
    {
        return std::abs(m_targetArea.lowerBoundVector.y()) - 1;
    }
    else
    {
        return m_targetArea.upperBoundVector.y();
    }
}

bool ProbeLauncherSimulator::isWithinTargetAfterAnyStep(const Vector2D& initialVelocityVector) const
{
    Vector2D positionVector{0, 0};
    Vector2D velocityVector = initialVelocityVector;

    while (true)
    {
        positionVector += velocityVector;

        if (isWithinTarget(positionVector))
        {
            return true;
        }

        if (positionVector.y() < m_targetArea.lowerBoundVector.y())
        {
            return false;
        }

        if (velocityVector.x() != 0)
        {
            velocityVector.x() = velocityVector.x() > 0 ? velocityVector.x() - 1 : velocityVector.x() + 1;
        }

        --velocityVector.y();
    }
}

bool ProbeLauncherSimulator::isWithinTarget(const Vector2D& positionVector) const
{
    return positionVector.x() >= m_targetArea.lowerBoundVector.x() &&
        positionVector.x() <= m_targetArea.upperBoundVector.x() &&
        positionVector.y() >= m_targetArea.lowerBoundVector.y() &&
        positionVector.y() <= m_targetArea.upperBoundVector.y();
}

}
}
}
