#include "Day25-HaltingProblem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day25;

    std::fstream fileIn("input.txt");
    std::vector<std::string> inputTuringMachineLines;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        inputTuringMachineLines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::diagnosticChecksum(inputTuringMachineLines) << std::endl;
}
