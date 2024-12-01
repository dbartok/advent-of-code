#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day12
{

class SpringConditionSolver
{
public:
    SpringConditionSolver(std::string springConditions, std::vector<int> damagedSpringGroupSizes);

    int64_t getNumPossibleArragements() const;

private:
    using MemoArgs = std::tuple<size_t, size_t, size_t>;

    std::string m_springConditions;
    std::vector<int> m_damagedSpringGroupSizes;

    mutable std::unordered_map<MemoArgs, int64_t, boost::hash<MemoArgs>> m_argsToMemoizedResult;

    int64_t getNumPossibleArragementsRecursiveMemoized(size_t currentPosition, size_t currentGroupIndex, size_t currentGroupExistingSize) const;
    int64_t getNumPossibleArragementsRecursive(size_t currentPosition, size_t currentGroupIndex, size_t currentGroupExistingSize) const;
};

}
}
}
