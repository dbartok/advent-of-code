#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day15
{

unsigned judgeFinalCountNoCriteria(unsigned aStart, unsigned bStart);
unsigned judgeFinalCountWithCriteria(unsigned aStart, unsigned bStart);

unsigned generatorStartFromLine(const std::string& line);

}
}
}
