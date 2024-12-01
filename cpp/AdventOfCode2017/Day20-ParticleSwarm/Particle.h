#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day20
{

class Particle
{
public:
    using Vector3D = Eigen::Matrix<long long, 3, 1>;

    Particle(unsigned particleID, Vector3D position, Vector3D velocity, Vector3D acceleration) noexcept;

    void stepTime();
    const Vector3D& getPosition() const noexcept;
    unsigned getParticleID() const noexcept;

private:
    unsigned m_particleID;

    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration;
};

}
}
}
