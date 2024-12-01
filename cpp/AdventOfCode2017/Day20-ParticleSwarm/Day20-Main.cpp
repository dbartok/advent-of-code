#include "Day20-ParticleSwarm.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day20;

    std::fstream fileIn("input.txt");
    std::vector<std::string> inputParticleLines;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        inputParticleLines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::particleIDClosestToOriginLongTerm(inputParticleLines) << std::endl;
    std::cout << "Second part: " << CurrentDay::numParticlesLeftAfterCollisions(inputParticleLines) << std::endl;
}
