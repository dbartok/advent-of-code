#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day10
{

class AdapterOrganizer
{
public:
    AdapterOrganizer(std::vector<int> joltageRatings);

    int getNumOneAndThreeJoltDifferencesMultiplied() const;
    int64_t getNumDistinctAdapterArrangements() const;

private:
    std::vector<int> m_joltageRatings;

    int numGivenJoltageDifferences(int targetDifference) const;
};

}
}
}
