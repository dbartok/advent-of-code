#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day12
{

using Vector3D = Eigen::Matrix<int, 3, 1>;

struct Moon
{
    Moon(Vector3D pos);

    Vector3D pos;
    Vector3D vel;

    bool operator==(const Moon& other) const = default;

    bool isAxisMatching(const Moon& other, size_t axisIndex) const;
};

class MoonMotionSimulator
{
public:
    MoonMotionSimulator(std::vector<Moon> moons);

    void simulate(unsigned numSteps);
    void simulateUntilRepetition();

    int getTotalEnergy() const;
    unsigned long long getNumSteps() const;

private:
    std::vector<Moon> m_moons;

    std::vector<Moon> m_initialMoons;
    unsigned long long m_numSteps;

    void step();
    void applyAllGravity();
    void applyAllVelocity();
    void simulateAxisUntilRepetition(size_t axisIndex);
    void reset();

    static void applyGravity(Moon& firstMoon, Moon& secondMoon);
    static void pullCloser(int p1, int p2, int& v1, int& v2);
};

}
}
}
