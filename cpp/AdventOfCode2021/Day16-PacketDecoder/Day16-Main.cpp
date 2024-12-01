#include "Day16-PacketDecoder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2021::Day16;

    std::fstream fileIn("input.txt");

    std::string transmissionString;
    std::getline(fileIn, transmissionString);

    std::cout << "First part: " << CurrentDay::sumOfAllVersionNumbersInPackets(transmissionString) << std::endl;
    std::cout << "Second part: " << CurrentDay::evaluateExpression(transmissionString) << std::endl;
}
