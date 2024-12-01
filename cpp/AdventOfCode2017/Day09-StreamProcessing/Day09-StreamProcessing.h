#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day09
{

unsigned totalScoreForAllGroups(const std::string& groupedString);
unsigned totalGarbageCount(const std::string& groupedString);

}
}
}
