#include "Day23-CrabCups.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2020::Day23;

    std::fstream fileIn("input.txt");
    std::string initialCupLabellingString;

    fileIn >> initialCupLabellingString;

    std::cout << "First part: " << CurrentDay::cupLabelsStartingFromCupOne(initialCupLabellingString, 100) << std::endl;
    std::cout << "Second part: " << CurrentDay::twoCupLabelsAfterCupOneMultipliedManyCups(initialCupLabellingString, 10'000'000) << std::endl;
}
