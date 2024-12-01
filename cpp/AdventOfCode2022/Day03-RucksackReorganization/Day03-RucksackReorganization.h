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
namespace Day03
{

int sumOfSharedItemPriorities(const std::vector<std::string>& rucksackContentsLines);
int sumOfGroupBadgePriorities(const std::vector<std::string>& rucksackContentsLines);

}
}
}
