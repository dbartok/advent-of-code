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
namespace Day07
{

int totalWinnings(const std::vector<std::string>& camelCardsLines);
int totalWinningsWithJokers(const std::vector<std::string>& camelCardsLines);

}
}
}
