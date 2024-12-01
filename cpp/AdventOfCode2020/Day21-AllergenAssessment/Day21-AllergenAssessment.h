#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day21
{

int numAppearancesOfIngredientsNotContainingAllergens(const std::vector<std::string>& foodLines);
std::string canonicalDangerousIngredientList(const std::vector<std::string>& foodLines);

}
}
}
