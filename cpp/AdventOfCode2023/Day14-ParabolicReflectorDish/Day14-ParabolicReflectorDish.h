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
namespace Day14
{

int totalLoadOnNorthSupportBeamsAfterNorthSlide(const std::vector<std::string>& platformLines);
int totalLoadOnNorthSupportBeamsAfterSeveralCycles(const std::vector<std::string>& platformLines);

}
}
}
