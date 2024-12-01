#include "Day01-TyrannyOfTheRocket.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2019::Day01;

    std::fstream fileIn("input.txt");
    std::vector<int> moduleMasses;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        const int moduleMass = std::stoi(lineBuffer);
        moduleMasses.push_back(moduleMass);
    }

    std::cout << "First part: " << CurrentDay::getSumOfFuelRequirements(moduleMasses) << std::endl;
    std::cout << "Second part: " << CurrentDay::getSumOfFuelRequirementsIncludingFuelItself(moduleMasses) << std::endl;
}
