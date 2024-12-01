#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day16
{

int64_t sumOfAllVersionNumbersInPackets(const std::string& transmissionString);
int64_t evaluateExpression(const std::string& transmissionString);

}
}
}
