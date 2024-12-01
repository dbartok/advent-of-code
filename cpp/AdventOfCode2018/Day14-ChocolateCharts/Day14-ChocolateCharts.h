#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day14
{

std::string scoresOfTenRecipesAfterSeveralRecipes(unsigned numRecipes);
unsigned numRecipesBeforeSequenceAppears(const std::string& sequence);

}
}
}
