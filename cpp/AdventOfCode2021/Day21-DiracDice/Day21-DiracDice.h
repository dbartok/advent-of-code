#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day21
{

int losingPlayerScoreTimesNumDiceRollsDeterministicDice(const std::vector<std::string>& startingPositionLines);
uint64_t numUniversesWithMoreWins(const std::vector<std::string>& startingPositionLines);

}
}
}
