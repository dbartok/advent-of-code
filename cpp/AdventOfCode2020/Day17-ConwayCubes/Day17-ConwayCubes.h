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
namespace Day17
{

int numCubesInActiveStateAfterBootCycle3D(const std::vector<std::string>& initialStateLines);
int numCubesInActiveStateAfterBootCycle4D(const std::vector<std::string>& initialStateLines);

}
}
}
