#pragma once

#include "MonkeyGroupSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/multiprecision/gmp.hpp>

#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day11
{

LargeNumberType levelOfMonkeyBusiness(const std::vector<std::string>& monkeyDescriptionLines);
LargeNumberType levelOfMonkeyBusinessWithRidiculousWorryLevels(const std::vector<std::string>& monkeyDescriptionLines);

}
}
}
