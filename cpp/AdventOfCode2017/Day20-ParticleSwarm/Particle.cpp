#include "Particle.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day20
{

Particle::Particle(unsigned particleID, Vector3D position, Vector3D velocity, Vector3D acceleration) noexcept
    : m_particleID(particleID)
    , m_position(std::move(position))
    , m_velocity(std::move(velocity))
    , m_acceleration(std::move(acceleration))
{

}

void Particle::stepTime()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

const Particle::Vector3D& Particle::getPosition() const noexcept
{
    return m_position;
}

unsigned Particle::getParticleID() const noexcept
{
    return m_particleID;
}

}
}
}
