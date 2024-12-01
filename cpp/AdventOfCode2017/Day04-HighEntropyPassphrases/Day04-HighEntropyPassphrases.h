#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day04
{

unsigned numPassphrasesNoDuplicateWords(const std::vector<std::string>& passphrase);
unsigned numPassphrasesNoAnagramWords(const std::vector<std::string>& passphrases);

}
}
}
