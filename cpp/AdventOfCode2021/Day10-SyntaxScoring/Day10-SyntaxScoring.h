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
namespace Day10
{

int totalSyntaxErrorScore(const std::vector<std::string>& syntaxLines);
int64_t middleAutocompleteScore(const std::vector<std::string>& syntaxLines);

}
}
}
