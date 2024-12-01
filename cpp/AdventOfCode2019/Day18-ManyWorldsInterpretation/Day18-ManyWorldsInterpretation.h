#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day18
{

int lengthOfShortestPathWithAllKeys(const std::vector<std::string>& vaultLines);
int lengthOfShortestPathWithAllKeysMultipleRobots(const std::vector<std::string>& vaultLines);

}
}
}
