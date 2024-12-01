#include "Day06-MemoryReallocation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day06;

    std::fstream fileIn("input.txt");
    CurrentDay::MemoryBanks inputBanks;

    unsigned inputBank;
    while (fileIn >> inputBank)
    {
        inputBanks.push_back(inputBank);
    }

    std::cout << "First part: " << CurrentDay::numUniqueRedistributions(inputBanks) << std::endl;
    std::cout << "Second part: " << CurrentDay::cyclesUntilReoccurs(inputBanks) << std::endl;
}
