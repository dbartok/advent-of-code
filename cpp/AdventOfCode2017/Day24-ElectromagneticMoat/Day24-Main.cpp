#include "Day24-ElectromagneticMoat.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day24;

    std::fstream fileIn("input.txt");
    std::vector<std::string> inputComponentLines;

    std::string lineBuffer;

    while (std::getline(fileIn, lineBuffer))
    {
        inputComponentLines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::strengthOfStrongestBridge(inputComponentLines) << std::endl;
    std::cout << "Second part: " << CurrentDay::strengthOfStrongestLongestBridge(inputComponentLines) << std::endl;
}
