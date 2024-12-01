#include "Day23-CoprocessorConflagration.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day23;

    std::fstream fileIn("input.txt");
    std::vector<std::string> inputInstructionStrings;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        inputInstructionStrings.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::numTimesMultInvoked(inputInstructionStrings) << std::endl;
    std::cout << "Second part: " << CurrentDay::overheatFinalValueOfH() << std::endl;
}
