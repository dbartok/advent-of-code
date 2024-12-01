#include "Day17-TrickShot.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2021::Day17;

    std::fstream fileIn("input.txt");

    std::string targetAreaString;
    std::getline(fileIn, targetAreaString);

    std::cout << "First part: " << CurrentDay::highestYPositionToHitTarget(targetAreaString) << std::endl;
    std::cout << "Second part: " << CurrentDay::numDistinctInitialVelocityValuesToHitTarget(targetAreaString) << std::endl;
}
