#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day03
{

int sumOfAllPartNumbers(const std::vector<std::string>& schematicLines);
int sumOfAllGearRatios(const std::vector<std::string>& schematicLines);

}
}
}
