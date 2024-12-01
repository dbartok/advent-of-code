#include "Day15-RambunctiousRecitation.h"

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
    namespace CurrentDay = AdventOfCode::Year2020::Day15;

    std::fstream fileIn("input.txt");
    const std::string intcodeProgramCommaSeparated
    {
        (std::istreambuf_iterator<char>(fileIn)),
        (std::istreambuf_iterator<char>())
    };

    std::vector<int> startingNumbers;
    AdventOfCode::Utils::splitStringIntoTypedVector(intcodeProgramCommaSeparated, startingNumbers, ',');

    std::cout << "First part: " << CurrentDay::nthNumberSpokenSmallN(startingNumbers) << std::endl;
    std::cout << "Second part: " << CurrentDay::nthNumberSpokenLargeN(startingNumbers) << std::endl;
}
