#include "Day14-DiskDefragmentation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day14;

    std::fstream fileIn("input.txt");
    std::string inputKeyString;

    fileIn >> inputKeyString;

    std::cout << "First part: " << CurrentDay::numSquaresUsed(inputKeyString) << std::endl;
    std::cout << "Second part: " << CurrentDay::numRegionsOfAdjcacentSquares(inputKeyString) << std::endl;
}
