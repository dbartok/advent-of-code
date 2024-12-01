#include "Day13-PacketScanners.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day13;

    std::fstream fileIn("input.txt");
    std::vector<std::string> inputScannerRangeLines;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        inputScannerRangeLines.push_back(lineBuffer);
    }

    std::cout << "First part: " << CurrentDay::severityOfWholeTrip(inputScannerRangeLines) << std::endl;
    std::cout << "Second part: " << CurrentDay::smallestDelayNotToGetCaught(inputScannerRangeLines) << std::endl;
}
