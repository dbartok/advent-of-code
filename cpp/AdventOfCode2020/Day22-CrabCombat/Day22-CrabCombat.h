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
namespace Day22
{

int winningPlayerScore(const std::vector<std::string>& startingDecksLines);
int winningPlayerScoreRecursiveCombat(const std::vector<std::string>& startingDecksLines);

}
}
}
