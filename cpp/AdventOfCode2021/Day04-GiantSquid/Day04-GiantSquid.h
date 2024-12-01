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
namespace Day04
{

int winningBoardFinalScore(const std::vector<std::string>& bingoSubsystemInputLines);
int lastToWinBoardFinalScore(const std::vector<std::string>& bingoSubsystemInputLines);

}
}
}
