#include "Day22-ReactorReboot.h"

#include "SubmarineReactorRebooter.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day22
{

RebootStep parseRebootStepLine(const std::string& rebootStepLine)
{
    std::regex rebootStepLineRegex(R"(((?:on)|(?:off)) x=(-?[0-9]+)..(-?[0-9]+),y=(-?[0-9]+)..(-?[0-9]+),z=(-?[0-9]+)..(-?[0-9]+))");
    std::smatch rebootStepLineMatch;
    std::regex_match(rebootStepLine, rebootStepLineMatch, rebootStepLineRegex);

    const bool state = rebootStepLineMatch[1].str() == "on";
    const int fromX = std::stoi(rebootStepLineMatch[2].str());
    const int toX = std::stoi(rebootStepLineMatch[3].str());
    const int fromY = std::stoi(rebootStepLineMatch[4].str());
    const int toY = std::stoi(rebootStepLineMatch[5].str());
    const int fromZ = std::stoi(rebootStepLineMatch[6].str());
    const int toZ = std::stoi(rebootStepLineMatch[7].str());

    Interval intervalX{fromX, toX};
    Interval intervalY{fromY, toY};
    Interval intervalZ{fromZ, toZ};

    return RebootStep{state, {std::move(intervalX), std::move(intervalY), std::move(intervalZ)}};
}

std::vector<RebootStep> parseRebootStepLines(const std::vector<std::string>& rebootStepLines)
{
    std::vector<RebootStep> rebootSteps;

    for (const auto& line : rebootStepLines)
    {
        RebootStep rebootStep = parseRebootStepLine(line);
        rebootSteps.push_back(std::move(rebootStep));
    }

    return rebootSteps;
}

uint64_t numCubesOnAfterInititializationProcedure(const std::vector<std::string>& rebootStepLines)
{
    std::vector<RebootStep> rebootSteps = parseRebootStepLines(rebootStepLines);
    SubmarineReactorRebooter rebooter{std::move(rebootSteps)};
    rebooter.executeRebootInitializationProcedure();
    return rebooter.getNumCubesOn();
}

uint64_t numCubesOnAfterFullRebootProcedure(const std::vector<std::string>& rebootStepLines)
{
    std::vector<RebootStep> rebootSteps = parseRebootStepLines(rebootStepLines);
    SubmarineReactorRebooter rebooter{std::move(rebootSteps)};
    rebooter.executeRebootFullRebootProcedure();
    return rebooter.getNumCubesOn();
}

}
}
}