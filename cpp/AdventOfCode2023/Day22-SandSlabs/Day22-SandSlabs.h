#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>

namespace AdventOfCode
{
namespace Year2023
{
namespace Day22
{

int numBricksSafeToDisintegrate(const std::vector<std::string>& brickSnapshotLines);
int sumOfNumBricksFallingAcrossAllDisintegrations(const std::vector<std::string>& brickSnapshotLines);

}
}
}
