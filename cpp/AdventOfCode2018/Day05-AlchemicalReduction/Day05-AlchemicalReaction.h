#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day05
{

unsigned getReducedPolymerLength(const std::string& polymerString);
unsigned getOneUnitRemovedShortestReducedLength(const std::string& polymerString);

}
}
}
