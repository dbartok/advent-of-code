#include "Day20-ParticleSwarm.h"

#include "Particle.h"
#include "ParticleSystem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned NUM_SIMULATION_STEPS = 1'000;

}

namespace AdventOfCode
{
namespace Year2017
{
namespace Day20
{

std::vector<Particle> createParticlesFromLines(const std::vector<std::string>& particleLines)
{
    const auto allSeparatorsPredicate = boost::is_any_of("pva=<>, ");
    std::vector<Particle> particles;

    unsigned particleID = 0;

    for (auto particleLine : particleLines)
    {
        // Remove leading and trailing separators
        boost::trim_if(particleLine, allSeparatorsPredicate);

        std::vector<std::string> tokens;
        boost::split(tokens, particleLine, allSeparatorsPredicate, boost::token_compress_on);

        if (tokens.size() != 9)
        {
            throw std::runtime_error("Expected exactly 9 tokens.");
        }

        Particle::Vector3D position{std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2])};
        Particle::Vector3D velocity{std::stoi(tokens[3]), std::stoi(tokens[4]), std::stoi(tokens[5])};
        Particle::Vector3D acceleration{std::stoi(tokens[6]), std::stoi(tokens[7]), std::stoi(tokens[8])};

        particles.emplace_back(particleID++, std::move(position), std::move(velocity), std::move(acceleration));
    }

    return particles;
}

unsigned particleIDClosestToOriginLongTerm(const std::vector<std::string>& particleLines)
{
    std::vector<Particle> particles = createParticlesFromLines(particleLines);

    ParticleSystem particleSystem{std::move(particles)};

    particleSystem.simulate(NUM_SIMULATION_STEPS);
    return particleSystem.particleIDClosestToOrigin();
}

unsigned numParticlesLeftAfterCollisions(const std::vector<std::string>& particleLines)
{
    std::vector<Particle> particles = createParticlesFromLines(particleLines);

    ParticleSystem particleSystem{std::move(particles)};

    particleSystem.simulateWithCollisions(NUM_SIMULATION_STEPS);
    return particleSystem.numParticles();
}

}
}
}
