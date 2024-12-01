#include "Day11-ChronalCharge.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day11;

    std::fstream fileIn("input.txt");
    int gridSerialNumber;

    fileIn >> gridSerialNumber;

    std::cout << "First part: " << CurrentDay::highestPowerSmallSquareCoordinates(gridSerialNumber) << std::endl;
    std::cout << "Second part: " << CurrentDay::highestPowerSquareCoordinatesAndSize(gridSerialNumber) << std::endl;
}
