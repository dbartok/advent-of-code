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
namespace Day06
{

int64_t numWaysRecordCanBeBeatenMultipliedTogether(const std::vector<std::string>& raceDescriptionLines);
int64_t numWaysRecordCanBeBeatenSingleRace(const std::vector<std::string>& raceDescriptionLines);

}
}
}
