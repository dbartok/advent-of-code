#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day17
{

int highestYPositionToHitTarget(const std::string& targetAreaString);
unsigned numDistinctInitialVelocityValuesToHitTarget(const std::string& targetAreaString);

}
}
}
