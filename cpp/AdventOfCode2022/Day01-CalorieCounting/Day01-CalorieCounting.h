#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day01
{

int maxTotalCaloriesCarried(const std::vector<std::string>&calorieLines);
int totalCaloriesCarriedByTopThreeElves(const std::vector<std::string>& calorieLines);

}
}
}
