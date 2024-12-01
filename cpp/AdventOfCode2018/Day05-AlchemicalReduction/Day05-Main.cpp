#include "Day05-AlchemicalReaction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day05;

    std::fstream fileIn("input.txt");
    std::string line;

    fileIn >> line;

    std::cout << "First part: " << CurrentDay::getReducedPolymerLength(line) << std::endl;
    std::cout << "Second part: " << CurrentDay::getOneUnitRemovedShortestReducedLength(line) << std::endl;
}
