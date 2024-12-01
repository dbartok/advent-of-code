#include "Day12-TheNBodyProblem.h"

#include "MoonMotionSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day12
{

std::vector<Moon> createMoons(const std::vector<std::string>& moonPositionLines)
{
    std::vector<Moon> moons;

    for (const auto& line : moonPositionLines)
    {
        std::regex coordinatesRegex(R"(<x=(-?[0-9]+), y=(-?[0-9]+), z=(-?[0-9]+)>)");
        std::smatch coordinatesMatch;

        std::regex_match(line, coordinatesMatch, coordinatesRegex);

        int posX = std::stoi(coordinatesMatch[1].str());
        int posY = std::stoi(coordinatesMatch[2].str());
        int posZ = std::stoi(coordinatesMatch[3].str());

        moons.emplace_back(Vector3D{posX, posY, posZ});
    }

    return moons;

}

int totalEnergyAfterSteps(const std::vector<std::string>& moonPositionLines, unsigned numSteps)
{
    std::vector<Moon> moons = createMoons(moonPositionLines);

    MoonMotionSimulator simulator{std::move(moons)};

    simulator.simulate(numSteps);

    return simulator.getTotalEnergy();
}

unsigned long long numStepsUntilRepetition(const std::vector<std::string>& moonPositionLines)
{
    std::vector<Moon> moons = createMoons(moonPositionLines);

    MoonMotionSimulator simulator{std::move(moons)};

    simulator.simulateUntilRepetition();

    return simulator.getNumSteps();
}

}
}
}
