#include "Day05-MazeOfTrampolines.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day05;

    std::fstream fileIn("input.txt");
    std::vector<int> inputInstructions;

    int inputOffset;
    while (fileIn >> inputOffset)
    {
        inputInstructions.push_back(inputOffset);
    }

    std::cout << "First part: " << CurrentDay::stepsInstructionsIncreasing(inputInstructions) << std::endl;
    std::cout << "Second part: " << CurrentDay::stepsInstructionsIncreasingDecreasing(inputInstructions) << std::endl;
}
