#include "Day10-MonitoringStation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2019::Day10;

    std::fstream fileIn("input.txt");

    std::string lineBuffer;
    std::vector<std::string> lines;
    while (std::getline(fileIn, lineBuffer))
    {
        lines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::maxNumAsteroidsDetected(lines) << std::endl;

    auto vaporizationOrder = CurrentDay::vaporizationOrder(lines);
    auto specialAsteroid = vaporizationOrder.at(199);
    std::cout << "Second part: " << specialAsteroid.first * 100 + specialAsteroid.second << std::endl;
}
