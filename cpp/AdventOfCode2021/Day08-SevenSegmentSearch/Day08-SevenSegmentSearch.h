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
namespace Day08
{

unsigned numEasyDigitsInOutput(const std::vector<std::string>& signalDecodingEntryLines);
int sumOfDecodedOutputValues(const std::vector<std::string>& signalDecodingEntryLines);

}
}
}
