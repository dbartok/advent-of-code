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
namespace Day05
{

int highestSeatID(const std::vector<std::string>& boardingPassLines);
int missingSeatID(const std::vector<std::string>& boardingPassLines);

}
}
}
