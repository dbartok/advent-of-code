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
namespace Day10
{

std::string serializedMessageWhenAligned(const std::vector<std::string>& starlightLines);
unsigned timeTakenUntilAligned(const std::vector<std::string>& starlightLines);

}
}
}
