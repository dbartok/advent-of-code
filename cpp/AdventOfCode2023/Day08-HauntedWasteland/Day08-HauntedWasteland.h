#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day08
{

int64_t numStepsRequiredToReachEndpoint(const std::vector<std::string>& mapLines);
int64_t numStepsRequiredToReachAllEndpointsSimultaneously(const std::vector<std::string>& mapLines);

}
}
}
