#include "Day09-StreamProcessing.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day09;

    std::fstream fileIn("input.txt");
    std::string groupedStringInput;

    fileIn >> groupedStringInput;

    std::cout << "First part: " << CurrentDay::totalScoreForAllGroups(groupedStringInput) << std::endl;
    std::cout << "Second part: " << CurrentDay::totalGarbageCount(groupedStringInput) << std::endl;
}
