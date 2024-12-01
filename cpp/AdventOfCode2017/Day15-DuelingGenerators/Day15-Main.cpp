#include "Day15-DuelingGenerators.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day15;

    std::fstream fileIn("input.txt");

    std::string generatorAStartLine;
    std::getline(fileIn, generatorAStartLine);
    const unsigned generatorAStartInput = CurrentDay::generatorStartFromLine(generatorAStartLine);

    std::string generatorBStartLine;
    std::getline(fileIn, generatorBStartLine);
    const unsigned generatorBStartInput = CurrentDay::generatorStartFromLine(generatorBStartLine);

    std::cout << "First part: " << CurrentDay::judgeFinalCountNoCriteria(generatorAStartInput, generatorBStartInput) << std::endl;
    std::cout << "Second part: " << CurrentDay::judgeFinalCountWithCriteria(generatorAStartInput, generatorBStartInput) << std::endl;
}
