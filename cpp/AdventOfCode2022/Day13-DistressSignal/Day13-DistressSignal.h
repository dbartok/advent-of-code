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
namespace Day13
{

int sumOfIndicesOfPairsInRightOrder(const std::vector<std::string>& distressSignalLines);
int decoderKeyForDistressSignal(const std::vector<std::string>& distressSignalLines);

}
}
}
