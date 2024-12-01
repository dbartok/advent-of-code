#include "SpringConditionSolver.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned SECOND_PART_FOLD_FACTOR = 5;

const char OPERATIONAL = '.';
const char DAMAGED = '#';
const char UNKNOWN = '?';

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day12
{

SpringConditionSolver::SpringConditionSolver(std::string springConditions, std::vector<int> damagedSpringGroupSizes)
    : m_springConditions{std::move(springConditions)}
    , m_damagedSpringGroupSizes{std::move(damagedSpringGroupSizes)}
{

}

int64_t SpringConditionSolver::getNumPossibleArragements() const
{
    return getNumPossibleArragementsRecursiveMemoized(0, 0, 0);
}

int64_t SpringConditionSolver::getNumPossibleArragementsRecursiveMemoized(size_t currentPosition, size_t currentGroupIndex, size_t currentGroupExistingSize) const
{
    MemoArgs memoArgs{currentPosition, currentGroupIndex, currentGroupExistingSize};
    const auto findResult = m_argsToMemoizedResult.find(memoArgs);
    if (findResult != m_argsToMemoizedResult.cend())
    {
        return findResult->second;
    }
    else
    {
        const int64_t result = getNumPossibleArragementsRecursive(currentPosition, currentGroupIndex, currentGroupExistingSize);
        m_argsToMemoizedResult.emplace(std::move(memoArgs), result);
        return result;
    }
}

int64_t SpringConditionSolver::getNumPossibleArragementsRecursive(size_t currentPosition, size_t currentGroupIndex, size_t currentGroupExistingSize) const
{
    if (currentPosition == m_springConditions.size())
    {
        const bool wereAllGroupsFoundAndNoNewGroupsStarted = (currentGroupIndex == m_damagedSpringGroupSizes.size() && currentGroupExistingSize == 0);
        const bool wereAllButLastGroupFoundAndCurrentGroupIsLastGroup = (currentGroupIndex == m_damagedSpringGroupSizes.size() - 1 && currentGroupExistingSize == m_damagedSpringGroupSizes.at(currentGroupIndex));

        if (wereAllGroupsFoundAndNoNewGroupsStarted || wereAllButLastGroupFoundAndCurrentGroupIsLastGroup)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int64_t numPossibleArragements = 0;
    const char currentSpringCondition = m_springConditions.at(currentPosition);

    if (currentSpringCondition == OPERATIONAL || currentSpringCondition == UNKNOWN)
    {
        if (currentGroupExistingSize == 0)
        {
            numPossibleArragements += getNumPossibleArragementsRecursiveMemoized(currentPosition + 1, currentGroupIndex, currentGroupExistingSize);
        }
        else if (currentGroupExistingSize == m_damagedSpringGroupSizes.at(currentGroupIndex))
        {
            numPossibleArragements += getNumPossibleArragementsRecursiveMemoized(currentPosition + 1, currentGroupIndex + 1, 0);
        }
    }

    if (currentSpringCondition == DAMAGED || currentSpringCondition == UNKNOWN)
    {
        if (currentGroupIndex < m_damagedSpringGroupSizes.size() && currentGroupExistingSize <= m_damagedSpringGroupSizes.at(currentGroupIndex))
        {
            numPossibleArragements += getNumPossibleArragementsRecursiveMemoized(currentPosition + 1, currentGroupIndex, currentGroupExistingSize + 1);
        }
    }

    return numPossibleArragements;
}

}
}
}
