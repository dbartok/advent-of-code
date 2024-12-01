#include "Day21-FractalArt.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day21;

    std::fstream fileIn("input.txt");
    std::vector<std::string> inputEnhancementRuleLines;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        inputEnhancementRuleLines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::numPixelsOnSmallIterations(inputEnhancementRuleLines) << std::endl;
    std::cout << "Second part: " << CurrentDay::numPixelsOnLargeIterations(inputEnhancementRuleLines) << std::endl;
}
