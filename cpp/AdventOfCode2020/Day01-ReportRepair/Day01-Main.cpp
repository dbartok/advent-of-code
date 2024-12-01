#include "Day01-ReportRepair.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2020::Day01;

    std::fstream fileIn("input.txt");
    std::vector<int> entries;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        const int entry = std::stoi(lineBuffer);
        entries.push_back(entry);
    }

    std::cout << "First part: " << CurrentDay::productOfTwoEntriesWithGivenSum(entries) << std::endl;
    std::cout << "Second part: " << CurrentDay::productOfThreeEntriesWithGivenSum(entries) << std::endl;
}
