#include "Day08-MemoryManeuver.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day08;

    std::fstream fileIn("input.txt");

    std::string line;
    std::getline(fileIn, line);

    std::vector<unsigned> nodeNumbers;
    AdventOfCode::Utils::splitStringIntoTypedVector(line, nodeNumbers, ' ');

    std::cout << "First part: " << CurrentDay::sumOfAllMetadataEntries(nodeNumbers) << std::endl;
    std::cout << "Second part: " << CurrentDay::valueOfRootNode(nodeNumbers) << std::endl;
}
