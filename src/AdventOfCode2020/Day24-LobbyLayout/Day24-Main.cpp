#include "Day24-LobbyLayout.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2020::Day24;

    std::fstream fileIn("input.txt");

    std::string lineBuffer;
    std::vector<std::string> lines;
    while (std::getline(fileIn, lineBuffer))
    {
        lines.push_back(std::move(lineBuffer));
    }


    std::cout << "First part: " << CurrentDay::numTilesWithBlackSideUpInInitialState(lines) << std::endl;
    std::cout << "Second part: " << CurrentDay::numTilesWithBlackSideUpAfterMultipleDays(lines) << std::endl;
}
