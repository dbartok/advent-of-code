#include "Day15-LensLibrary.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2023::Day15;

    std::fstream fileIn("input.txt");

    std::string line;
    std::getline(fileIn, line);

    std::cout << "First part: " << CurrentDay::sumOfHashResults(line) << std::endl;
    std::cout << "Second part: " << CurrentDay::focusingPowerOfLensConfiguration(line) << std::endl;
}
