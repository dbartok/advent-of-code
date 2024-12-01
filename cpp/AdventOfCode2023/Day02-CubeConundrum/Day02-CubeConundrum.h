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
namespace Day02
{

int sumOfIDsOfPossibleGames(const std::vector<std::string>& gameRecordLines);
int sumOfPowerOfMinimalSets(const std::vector<std::string>& gameRecordLines);

}
}
}
