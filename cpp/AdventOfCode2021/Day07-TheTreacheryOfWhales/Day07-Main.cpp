#include "Day07-TheTreacheryOfWhales.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2021::Day07;

    std::fstream fileIn("input.txt");

    std::string horizontalPositionsString;
    std::getline(fileIn, horizontalPositionsString);

    std::vector<int> horizontalPositions;
    AdventOfCode::Utils::splitStringIntoTypedVector(horizontalPositionsString, horizontalPositions, ',');

    std::cout << "First part: " << CurrentDay::leastAmountOfFuelSpentToAlign(horizontalPositions) << std::endl;
    std::cout << "Second part: " << CurrentDay::leastAmountOfFuelSpentToAlignWithIncreasingCosts(horizontalPositions) << std::endl;
}
