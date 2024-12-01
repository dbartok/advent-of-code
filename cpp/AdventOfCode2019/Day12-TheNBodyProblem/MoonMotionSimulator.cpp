#include "MoonMotionSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/math/common_factor_rt.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day12
{


Moon::Moon(Vector3D pos)
    : pos{std::move(pos)}
    , vel{0, 0, 0}
{

}

bool Moon::isAxisMatching(const Moon& other, size_t axisIndex) const
{
    return pos[axisIndex] == other.pos[axisIndex] && vel[axisIndex] == other.vel[axisIndex];
}

MoonMotionSimulator::MoonMotionSimulator(std::vector<Moon> moons)
    : m_initialMoons{std::move(moons)}
{
    reset();
}

void MoonMotionSimulator::simulate(unsigned numSteps)
{
    for (size_t i = 0; i < numSteps; ++i)
    {
        step();
    }
}

void MoonMotionSimulator::simulateUntilRepetition()
{
    std::vector<unsigned long long> individualAxisResults;

    for (int axisIndex = 0; axisIndex <= 2; ++axisIndex)
    {
        reset();

        simulateAxisUntilRepetition(axisIndex);

        individualAxisResults.push_back(getNumSteps());
    }

    m_numSteps = std::accumulate(individualAxisResults.cbegin(), individualAxisResults.cend(), 1ull, [](auto total, auto current)
                                    {
                                        return boost::math::lcm(total, current);
                                    });
}

int MoonMotionSimulator::getTotalEnergy() const
{
    return std::accumulate(m_moons.cbegin(), m_moons.cend(), 0, [](int total, const Moon& moon)
                            {
                                return total + (moon.pos.cwiseAbs().sum() * moon.vel.cwiseAbs().sum());
                            });
}

unsigned long long MoonMotionSimulator::getNumSteps() const
{
    return m_numSteps;
}

void MoonMotionSimulator::step()
{
    ++m_numSteps;
    applyAllGravity();
    applyAllVelocity();
}

void MoonMotionSimulator::applyAllGravity()
{
    for (auto firstMoonIter = m_moons.begin(); firstMoonIter != m_moons.end(); ++firstMoonIter)
    {
        for (auto secondMoonIter = std::next(firstMoonIter); secondMoonIter != m_moons.end(); ++secondMoonIter)
        {
            applyGravity(*firstMoonIter, *secondMoonIter);
        }
    }
}

void MoonMotionSimulator::applyAllVelocity()
{
    for (auto& moon : m_moons)
    {
        moon.pos += moon.vel;
    }
}

void MoonMotionSimulator::simulateAxisUntilRepetition(size_t axisIndex)
{
    while (true)
    {
        step();

        bool isRepeat = std::equal(m_moons.cbegin(), m_moons.cend(), m_initialMoons.cbegin(), [axisIndex](const auto& lhs, const auto& rhs)
                                    {
                                        return lhs.isAxisMatching(rhs, axisIndex);
                                    });

        if (isRepeat)
        {
            break;
        }
    }
}

void MoonMotionSimulator::reset()
{
    m_numSteps = 0;
    m_moons = m_initialMoons;
}

void MoonMotionSimulator::applyGravity(Moon& firstMoon, Moon& secondMoon)
{
    for (int axisIndex = 0; axisIndex <= 2; ++axisIndex)
    {
        int& firstMoonPositionCoordinate = firstMoon.pos[axisIndex];
        int& secondMoonPositionCoordinate = secondMoon.pos[axisIndex];

        int& firstMoonVelocityCoordinate = firstMoon.vel[axisIndex];
        int& secondMoonVelocityCoordinate = secondMoon.vel[axisIndex];

        pullCloser(firstMoonPositionCoordinate, secondMoonPositionCoordinate, firstMoonVelocityCoordinate, secondMoonVelocityCoordinate);
    }
}

void MoonMotionSimulator::pullCloser(int p1, int p2, int& v1, int& v2)
{
    if (p1 < p2)
    {
        ++v1;
        --v2;
    }
    else if (p1 > p2)
    {
        --v1;
        ++v2;
    }
}

}
}
}
