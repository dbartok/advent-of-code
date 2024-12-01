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
namespace Day05
{

int64_t lowestLocationNumberCorrespondingToSeed(const std::vector<std::string>& almanacLines);
int64_t lowestLocationNumberCorrespondingToSeedWithSeedRanges(const std::vector<std::string>& almanacLines);

}
}
}
