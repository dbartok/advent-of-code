#include "ParticleSystem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>

#include <algorithm>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day20
{

ParticleSystem::ParticleSystem(std::vector<Particle> particles) noexcept
    : m_particles{std::move(particles)}
{

}

void ParticleSystem::simulate(unsigned numSteps)
{
    for (unsigned i = 0; i < numSteps; ++i)
    {
        for (auto& particle : m_particles)
        {
            particle.stepTime();
        }
    }
}

void ParticleSystem::simulateWithCollisions(unsigned numSteps)
{
    for (unsigned i = 0; i < numSteps; ++i)
    {
        simulate(1);
        removeAllCollidingParticles();
    }
}

unsigned ParticleSystem::particleIDClosestToOrigin() const
{
    if (m_particles.empty())
    {
        throw std::runtime_error("No particles.");
    }

    const auto minDistanceIter = std::min_element(m_particles.cbegin(), m_particles.cend(), [](const Particle& lhs, const Particle& rhs)
                                                  {
                                                      return lhs.getPosition().cwiseAbs().sum() < rhs.getPosition().cwiseAbs().sum();
                                                  });

    return minDistanceIter->getParticleID();
}

unsigned ParticleSystem::numParticles() const noexcept
{
    return m_particles.size();
}

struct Vector3DHash
{
    size_t operator()(const Particle::Vector3D& vec) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, vec.x());
        boost::hash_combine(seed, vec.y());
        boost::hash_combine(seed, vec.z());

        return seed;
    }
};

void ParticleSystem::removeAllCollidingParticles()
{
    std::unordered_multimap<Particle::Vector3D, Particle, Vector3DHash> positionToParticleMap;

    // Move elements of m_particles into the position map
    for (auto& particle : m_particles)
    {
        auto position = particle.getPosition();
        positionToParticleMap.emplace(std::move(position), std::move(particle));
    }

    m_particles.clear();

    // Non-colliding particles are the ones with a unique position
    // Rebuild m_particles by moving these back from the position map
    for (auto& element : positionToParticleMap)
    {
        if (positionToParticleMap.count(element.first) == 1)
        {
            m_particles.push_back(std::move(element.second));
        }
    }
}

}
}
}
