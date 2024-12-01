#include "Day01-TyrannyOfTheRocket.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day01
{

constexpr int getFuelRequirement(int moduleMass) noexcept
{
    return (moduleMass / 3) - 2;
}

int getFuelRequirementIncludingFuelItself(int moduleMass)
{
    const int fuelRequirement = getFuelRequirement(moduleMass);

    if (fuelRequirement <= 0)
    {
        return 0;
    }

    return fuelRequirement + getFuelRequirementIncludingFuelItself(fuelRequirement);
}

int getSumOfFuelRequirements(const std::vector<int>& moduleMasses)
{
    return std::accumulate(moduleMasses.cbegin(), moduleMasses.cend(), 0,
                           [](int acc, int mass) noexcept
                           {
                               return acc + getFuelRequirement(mass);
                           });
}

int getSumOfFuelRequirementsIncludingFuelItself(const std::vector<int>& moduleMasses)
{
    return std::accumulate(moduleMasses.cbegin(), moduleMasses.cend(), 0,
                           [](int acc, int mass)
                           {
                               return acc + getFuelRequirementIncludingFuelItself(mass);
                           });
}

}
}
}
