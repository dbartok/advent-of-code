#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day19
{

std::string lettersVisited(const std::vector<std::string>& diagramLines);
unsigned totalNumStepsForPacket(const std::vector<std::string>& diagramLines);

}
}
}
