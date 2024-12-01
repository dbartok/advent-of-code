#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day05
{

std::string cratesOnTopOfEachStack(const std::vector<std::string>& startingStacksAndRearrangementProcedureLines);
std::string cratesOnTopOfEachStackWithNewerTypeCrane(const std::vector<std::string>& startingStacksAndRearrangementProcedureLines);

}
}
}
