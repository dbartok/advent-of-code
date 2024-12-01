#include "Day22-SporificaVirus.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day22;

    std::fstream fileIn("input.txt");
    std::vector<std::string> initialVirusPosLines;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        initialVirusPosLines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::basicVirusInfectingBursts(initialVirusPosLines) << std::endl;
    std::cout << "Second part: " << CurrentDay::evolvedVirusInfectingBursts(initialVirusPosLines) << std::endl;
}
