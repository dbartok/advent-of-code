#include "DayX-PuzzleName.h" //TODO: Change to the name of the puzzle

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

//TODO: Implement parsing and driver
int main()
{
    namespace CurrentDay = AdventOfCode::YearXXXX::DayXX;

    std::fstream fileIn("input.txt");
    int puzzleInput;

    fileIn >> puzzleInput;

    std::cout << "First part: " << CurrentDay::solution1(puzzleInput) << std::endl;
    std::cout << "Second part: " << CurrentDay::solution2(puzzleInput) << std::endl;
}
