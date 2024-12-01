#include "Day06-ChronalCoordinates.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day06;

    std::fstream fileIn("input.txt");

    std::string lineBuffer;
    std::vector<std::string> lines;
    while (std::getline(fileIn, lineBuffer))
    {
        lines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::sizeOfLargestNonInfiniteArea(lines) << std::endl;
    std::cout << "Second part: " << CurrentDay::sizeOfAreaWithinGivenDistance(lines) << std::endl;
}
