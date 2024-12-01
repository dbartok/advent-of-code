#include "Day20-ARegularMap.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day20;

    std::fstream fileIn("input.txt");

    std::string roomLayoutRegex;
    fileIn >> roomLayoutRegex;

    std::cout << "First part: " << CurrentDay::distanceToFarthestRoom(roomLayoutRegex) << std::endl;
    std::cout << "Second part: " << CurrentDay::numRoomsWithLargeDistance(roomLayoutRegex) << std::endl;
}
