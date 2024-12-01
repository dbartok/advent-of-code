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
namespace Day20
{

int64_t sumOfGroveCoordinates(const std::vector<std::string>& encryptedFileLines);
int64_t sumOfGroveCoordinatesWithDecryptionRoutine(const std::vector<std::string>& encryptedFileLines);

}
}
}
