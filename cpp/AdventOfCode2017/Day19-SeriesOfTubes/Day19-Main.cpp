#include "Day19-SeriesOfTubes.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day19;

    std::fstream fileIn("input.txt");
    std::vector<std::string> inputDiagramLines;

    std::string inputDiagramLine;
    while (std::getline(fileIn, inputDiagramLine))
    {
        inputDiagramLines.push_back(std::move(inputDiagramLine));
    }

    std::cout << "First part: " << CurrentDay::lettersVisited(inputDiagramLines) << std::endl;
    std::cout << "Second part: " << CurrentDay::totalNumStepsForPacket(inputDiagramLines) << std::endl;
}
