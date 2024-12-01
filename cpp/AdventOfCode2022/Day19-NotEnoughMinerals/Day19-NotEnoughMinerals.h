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
namespace Day19
{

int sumOfBlueprintQualityLevels(const std::vector<std::string>& blueprintLines);
int productOfFirstFewBlueprintMaxGeodesWithMoreTime(const std::vector<std::string>& blueprintLines);

}
}
}
