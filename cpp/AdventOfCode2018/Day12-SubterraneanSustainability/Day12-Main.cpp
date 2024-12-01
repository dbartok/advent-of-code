#include "Day12-SubterraneanSustainability.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day12;

    std::fstream fileIn("input.txt");

    std::string initialStateLine;
    std::getline(fileIn, initialStateLine);

    std::string lineBuffer;
    std::vector<std::string> neighborPatterLines;
    while (std::getline(fileIn, lineBuffer))
    {
        if (!lineBuffer.empty())
        {
            neighborPatterLines.push_back(std::move(lineBuffer));
        }
    }

    std::cout << "First part: " << CurrentDay::sumOfPotNumbersWithPlantAfterGrowthShortTime(initialStateLine, neighborPatterLines) << std::endl;
    std::cout << "Second part: " << CurrentDay::sumOfPotNumbersWithPlantAfterGrowthLongTime(initialStateLine, neighborPatterLines) << std::endl;
}
