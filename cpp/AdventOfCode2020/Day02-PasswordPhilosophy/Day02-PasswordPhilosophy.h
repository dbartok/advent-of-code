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
namespace Day02
{

int numValidPasswordsWithRangePolicy(const std::vector<std::string>& passwordWithPolicyLines);
int numValidPasswordsWithPositionPolicy(const std::vector<std::string>& passwordWithPolicyLines);

}
}
}
