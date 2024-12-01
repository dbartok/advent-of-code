#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day20
{

unsigned numPixelsLitAfterSmallEnhancement(const std::vector<std::string>& imageEnhancementAlgorithmAndInputImageLines);
unsigned numPixelsLitAfterLargeEnhancement(const std::vector<std::string>& imageEnhancementAlgorithmAndInputImageLines);

}
}
}
