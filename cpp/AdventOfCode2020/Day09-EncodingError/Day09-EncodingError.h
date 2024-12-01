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
namespace Day09
{

int64_t firstInvalidNumber(const std::vector<int64_t>& numbers, size_t windowLength);
int64_t encryptionWeakness(const std::vector<int64_t>& numbers, size_t windowLength);

}
}
}
