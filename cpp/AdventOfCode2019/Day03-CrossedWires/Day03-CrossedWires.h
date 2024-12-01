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
namespace Day03
{

int distanceToClosestIntersection(const std::vector<std::string>& wireLines);
int combinedWireStepsToClosestIntersection(const std::vector<std::string>& wireLines);

}
}
}
