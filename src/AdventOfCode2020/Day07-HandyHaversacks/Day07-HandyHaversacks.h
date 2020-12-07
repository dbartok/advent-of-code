#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

int numBagColorsThatCanContainShinyGold(const std::vector<std::string>& lines);
int numTotalBagsContainedInsideShinyGold(const std::vector<std::string>& lines);

}
