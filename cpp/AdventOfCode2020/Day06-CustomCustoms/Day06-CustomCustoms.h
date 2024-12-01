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
namespace Day06
{

int sumAnyoneAnsweredYes(const std::vector<std::string>& lines);
int sumEveryoneAnsweredYes(const std::vector<std::string>& lines);

}
}
}
