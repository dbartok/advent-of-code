#include "Day24-ImmuneSystemSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day24;

    std::fstream fileIn("input.txt");

    std::string lineBuffer;
    std::vector<std::string> lines;
    while (std::getline(fileIn, lineBuffer))
    {
        lines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::numUnitsOfWinningArmy(lines) << std::endl;
    std::cout << "Second part: " << CurrentDay::numUnitsImmuneSystemSmallestBoost(lines) << std::endl;
}