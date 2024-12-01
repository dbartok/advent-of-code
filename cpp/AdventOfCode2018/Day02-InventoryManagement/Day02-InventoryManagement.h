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
namespace Day02
{

unsigned checksumTwoOrThreeOfAnyLetter(const std::vector<std::string>& words);
std::string commonLettersBetweenOneCharacterDiff(const std::vector<std::string>& words);

}
}
}
