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
namespace Day07
{

int totalSizeOfSmallDirectories(const std::vector<std::string>& terminalOutputLines);
int sizeOfSmallestDirectoryToDelete(const std::vector<std::string>& terminalOutputLines);

}
}
}
