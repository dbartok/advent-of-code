#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day22
{

uint64_t numCubesOnAfterInititializationProcedure(const std::vector<std::string>& rebootStepLines);
uint64_t numCubesOnAfterFullRebootProcedure(const std::vector<std::string>& rebootStepLines);

}
}
}
