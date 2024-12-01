//TODO: Rename to current day and name of the puzzle
#include "DayXX-PuzzleName.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    //TODO: Rename to current year and day
    namespace CurrentDay = AdventOfCode::YearXXXX::DayXX;

    std::fstream fileIn("input.txt");
    int puzzleInput;

    fileIn >> puzzleInput;

    std::cout << "First part: " << CurrentDay::solution1(puzzleInput) << std::endl;
    std::cout << "Second part: " << CurrentDay::solution2(puzzleInput) << std::endl;
}
