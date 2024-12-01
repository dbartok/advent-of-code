#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day15
{

unsigned outcomeOfCombat(const std::vector<std::string>& mapLines);
unsigned outcomeOfCombatIfElvesBarelyWin(const std::vector<std::string>& mapLines);

}
}
}
