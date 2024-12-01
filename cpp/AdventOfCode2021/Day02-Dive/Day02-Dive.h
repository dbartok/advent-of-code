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
namespace Day02
{

int finalHorizontalPositionAndDepthMultiplied(const std::vector<std::string>& instructionLines);
int finalHorizontalPositionAndDepthMultipliedWithAdjustedCourse(const std::vector<std::string>& instructionLines);

}
}
}
