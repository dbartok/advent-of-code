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
namespace Day13
{

unsigned numVisibleDotsAfterFirstFold(const std::vector<std::string>& instructionManualLines);
std::string thermalCameraActivationCode(const std::vector<std::string>& instructionManualLines);

}
}
}
