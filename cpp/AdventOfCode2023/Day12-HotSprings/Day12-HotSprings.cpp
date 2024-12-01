#include "Day12-HotSprings.h"

#include "SpringConditionSolver.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned SECOND_PART_FOLD_FACTOR = 5;

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day12
{

SpringConditionSolver parseSpringConditionsLine(const std::string& springConditionsLine, unsigned foldFactor)
{
    std::vector<std::string> tokens;
    boost::split(tokens, springConditionsLine, boost::is_any_of(" "));

    std::vector<int> damagedSpringGroupSizes;
    AdventOfCode::Utils::splitStringIntoTypedVector(tokens.at(1), damagedSpringGroupSizes, ',');

    std::string unfoldedSpringConditions;
    std::vector<int> unfoldedDamagedSpringGroupSizes;

    for (unsigned i = 1; i <= foldFactor; ++i)
    {
        unfoldedSpringConditions += tokens.at(0);
        if (i != foldFactor)
        {
            unfoldedSpringConditions += "?";
        }

        std::copy(damagedSpringGroupSizes.cbegin(), damagedSpringGroupSizes.cend(), std::back_inserter(unfoldedDamagedSpringGroupSizes));
    }

    return {std::move(unfoldedSpringConditions), std::move(unfoldedDamagedSpringGroupSizes)};
}

std::vector<SpringConditionSolver> parseSpringConditionsLines(const std::vector<std::string>& springConditionsLines, unsigned foldFactor = 1)
{
    std::vector<SpringConditionSolver> springConditionSolvers;

    for (const auto& springConditionsLine : springConditionsLines)
    {
        SpringConditionSolver springConditionSolver = parseSpringConditionsLine(springConditionsLine, foldFactor);
        springConditionSolvers.push_back(std::move(springConditionSolver));
    }

    return springConditionSolvers;
}

int64_t sumOfAllPossibleArrangements(const std::vector<std::string>& springConditionsLines)
{
    std::vector<SpringConditionSolver> springConditionSolvers = parseSpringConditionsLines(springConditionsLines);

    return std::accumulate(springConditionSolvers.cbegin(), springConditionSolvers.cend(), 0ll, [](int64_t acc, const auto& solver)
                           {
                               return acc + solver.getNumPossibleArragements();
                           });
}

int64_t sumOfAllPossibleArrangementsUnfolded(const std::vector<std::string>& springConditionsLines)
{
    std::vector<SpringConditionSolver> springConditionSolvers = parseSpringConditionsLines(springConditionsLines, SECOND_PART_FOLD_FACTOR);

    return std::accumulate(springConditionSolvers.cbegin(), springConditionSolvers.cend(), 0ll, [](int64_t acc, const auto& solver)
                           {
                               return acc + solver.getNumPossibleArragements();
                           });
}

}
}
}