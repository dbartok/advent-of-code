#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day06
{

int numCharactersProcessedBeforeStartOfPacketMarker(const std::string& data);
int numCharactersProcessedBeforeStartOfMessage(const std::string& data);

}
}
}
