#pragma once

#include "Particle.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day20
{

class ParticleSystem
{
public:
    ParticleSystem(std::vector<Particle> particles) noexcept;
    void simulate(unsigned numSteps);
    void simulateWithCollisions(unsigned numSteps);
    unsigned particleIDClosestToOrigin() const;
    unsigned numParticles() const noexcept;

private:
    std::vector<Particle> m_particles;

    void removeAllCollidingParticles();
};

}
}
}
