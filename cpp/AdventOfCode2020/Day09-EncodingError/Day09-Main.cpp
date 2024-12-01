#include "Day09-EncodingError.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2020::Day09;

    std::fstream fileIn("input.txt");
    std::vector<int64_t> numbers;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        const int64_t entry = std::stoll(lineBuffer);
        numbers.push_back(entry);
    }

    std::cout << "First part: " << CurrentDay::firstInvalidNumber(numbers, 25) << std::endl;
    std::cout << "Second part: " << CurrentDay::encryptionWeakness(numbers, 25) << std::endl;
}
