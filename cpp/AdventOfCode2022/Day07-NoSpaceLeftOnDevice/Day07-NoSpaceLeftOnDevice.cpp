#include "Day07-NoSpaceLeftOnDevice.h"

#include "TerminalOutputAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day07
{

int totalSizeOfSmallDirectories(const std::vector<std::string>& terminalOutputLines)
{
    TerminalOutputAnalyzer terminalOutputAnalyzer{terminalOutputLines};

    terminalOutputAnalyzer.reconstructFilesystem();

    return terminalOutputAnalyzer.getTotalSizeOfSmallDirectories();
}

int sizeOfSmallestDirectoryToDelete(const std::vector<std::string>& terminalOutputLines)
{
    TerminalOutputAnalyzer terminalOutputAnalyzer{terminalOutputLines};

    terminalOutputAnalyzer.reconstructFilesystem();

    return terminalOutputAnalyzer.getSizeOfSmallestDirectoryToDelete();
}

}
}
}