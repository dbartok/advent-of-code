#include "Day10-AdapterArray.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

#include "AdapterOrganizer.h"

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day10
{

int numOneAndThreeJoltDifferencesMultiplied(std::vector<int> joltageRatings)
{
    AdapterOrganizer adapterOrganizer{std::move(joltageRatings)};
    return adapterOrganizer.getNumOneAndThreeJoltDifferencesMultiplied();
}

int64_t numDistinctAdapterArrangements(std::vector<int> joltageRatings)
{
    AdapterOrganizer adapterOrganizer{std::move(joltageRatings)};
    return adapterOrganizer.getNumDistinctAdapterArrangements();
}

}
}
}
