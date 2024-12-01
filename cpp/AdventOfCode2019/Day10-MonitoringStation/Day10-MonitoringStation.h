#pragma once

#include "AsteroidMap.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day10
{

unsigned maxNumAsteroidsDetected(const std::vector<std::string> asteroidMapLines);
std::vector<Coordinates> vaporizationOrder(const std::vector<std::string> asteroidMapLines);

}
}
}
