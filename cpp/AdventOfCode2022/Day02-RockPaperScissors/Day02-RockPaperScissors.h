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
namespace Day02
{

int totalScoreAccordingToStrategyGuide(const std::vector<std::string>& strategyGuideLines);
int totalScoreAccordingToElfInstructions(const std::vector<std::string>& strategyGuideLines);

}
}
}
