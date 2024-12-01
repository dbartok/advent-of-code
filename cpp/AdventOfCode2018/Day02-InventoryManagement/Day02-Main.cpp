#include "Day02-InventoryManagement.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day02;

    std::fstream fileIn("input.txt");
    std::vector<std::string> words;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        words.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::checksumTwoOrThreeOfAnyLetter(words) << std::endl;
    std::cout << "Second part: " << CurrentDay::commonLettersBetweenOneCharacterDiff(words) << std::endl;
}
