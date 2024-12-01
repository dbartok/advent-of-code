#include "Day15-BeverageBandits.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day15;

    std::fstream fileIn("input.txt");

    std::string lineBuffer;
    std::vector<std::string> lines;
    while (std::getline(fileIn, lineBuffer))
    {
        if (!lineBuffer.empty())
        {
            lines.push_back(std::move(lineBuffer));
        }
    }

    std::cout << "First part: " << CurrentDay::outcomeOfCombat(lines) << std::endl;
    std::cout << "Second part: " << CurrentDay::outcomeOfCombatIfElvesBarelyWin(lines) << std::endl;
}
