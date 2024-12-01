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
namespace Day04
{

int numValidPassports(const std::vector<std::string>& batchFileLines);
int numValidPassportsStrict(const std::vector<std::string>& batchFileLines);

}
}
}
