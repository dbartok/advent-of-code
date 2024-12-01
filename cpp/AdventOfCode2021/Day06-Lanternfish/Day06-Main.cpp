#include "Day06-Lanternfish.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2021::Day06;
    std::fstream fileIn("input.txt");

    std::string initialStateString;
    std::getline(fileIn, initialStateString);

    std::vector<int> initialState;
    AdventOfCode::Utils::splitStringIntoTypedVector(initialStateString, initialState, ',');

    std::cout << "First part: " << CurrentDay::numLanternfishAfterSmallNumberOfDays(initialState) << std::endl;
    std::cout << "Second part: " << CurrentDay::numLanternfishAfterLargeNumberOfDays(initialState) << std::endl;
}
