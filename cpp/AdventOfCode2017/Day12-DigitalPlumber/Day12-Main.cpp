#include "Day12-DigitalPlumber.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day12;

    std::fstream fileIn("input.txt");
    std::vector<std::string> inputNeighborsLines;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        inputNeighborsLines.push_back(lineBuffer);
    }

    std::cout << "First part: " << CurrentDay::numNodesInGroupNodeZero(inputNeighborsLines) << std::endl;
    std::cout << "Second part: " << CurrentDay::numTotalGroups(inputNeighborsLines) << std::endl;
}
