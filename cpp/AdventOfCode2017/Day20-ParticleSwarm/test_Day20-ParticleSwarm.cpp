#include "Day20-ParticleSwarm.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day20;

TEST_CLASS(Day20ParticleSwarm)
{
public:

    TEST_METHOD(particleIDClosestToOriginLongTerm_SimpleTests)
    {
        const std::vector<std::string> particleLines =
        {
            "p=< 3,0,0>, v=< 2,0,0>, a=<-1,0,0>",
            "p=< 4,0,0>, v=< 0,0,0>, a=<-2,0,0>"
        };

        Assert::AreEqual(0u, CurrentDay::particleIDClosestToOriginLongTerm(particleLines));
    }

    TEST_METHOD(numParticlesLeftAfterCollisions_SimpleTests)
    {
        const std::vector<std::string> particleLines =
        {
            "p=<-6,0,0>, v=< 3,0,0>, a=< 0,0,0>",
            "p=<-4,0,0>, v=< 2,0,0>, a=< 0,0,0>",
            "p=<-2,0,0>, v=< 1,0,0>, a=< 0,0,0>",
            "p=< 3,0,0>, v=<-1,0,0>, a=< 0,0,0>"
        };

        Assert::AreEqual(1u, CurrentDay::numParticlesLeftAfterCollisions(particleLines));
    }

};
