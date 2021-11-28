#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day09
{

unsigned winningElfsScore(const std::string& gameDescriptionLine);
unsigned winningElfsScoreLongerGame(const std::string& gameDescriptionLine);

}
}
}
