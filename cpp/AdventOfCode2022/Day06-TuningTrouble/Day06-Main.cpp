#include "Day06-TuningTrouble.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2022::Day06;

    std::fstream fileIn("input.txt");

    std::string line;
    std::getline(fileIn, line);

    std::cout << "First part: " << CurrentDay::numCharactersProcessedBeforeStartOfPacketMarker(line) << std::endl;
    std::cout << "Second part: " << CurrentDay::numCharactersProcessedBeforeStartOfMessage(line) << std::endl;
}
