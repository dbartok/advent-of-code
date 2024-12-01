#include "Day18-BoilingBoulders.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2022::Day18;

    std::fstream fileIn("input.txt");

    std::string lineBuffer;
    std::vector<std::string> lines;
    while (std::getline(fileIn, lineBuffer))
    {
        lines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::surfaceAreaOfScannedLavaDroplet(lines) << std::endl;
    std::cout << "Second part: " << CurrentDay::outerSurfaceAreaOfScannedLavaDroplet(lines) << std::endl;
}
