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
namespace Day03
{

int submarinePowerConsumption(const std::vector<std::string>& diagnosticReportLines);
int lifeSupportRating(const std::vector<std::string>& diagnosticReportLines);

}
}
}
