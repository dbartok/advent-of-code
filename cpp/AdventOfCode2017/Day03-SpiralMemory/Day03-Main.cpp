#include "Day03-SpiralMemory.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day03;

    std::fstream fileIn("input.txt");
    unsigned input;

    fileIn >> input;

    std::cout << "First part: " << CurrentDay::stepsToCarryBack(input) << std::endl;
    std::cout << "Second part: " << CurrentDay::stressTestFirstValueGreaterThan(input) << std::endl;
}
