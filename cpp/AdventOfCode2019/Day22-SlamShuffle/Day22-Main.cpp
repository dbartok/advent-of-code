#include "Day22-SlamShuffle.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2019::Day22;

    std::fstream fileIn("input.txt");

    std::string lineBuffer;
    std::vector<std::string> lines;
    while (std::getline(fileIn, lineBuffer))
    {
        lines.push_back(std::move(lineBuffer));
    }

    auto cards = CurrentDay::cardsAfterShuffle(lines, 10007);
    std::cout << "First part: " << (std::find(cards.cbegin(), cards.cend(), 2019) - cards.cbegin()) << std::endl;
    std::cout << "Second part: " << CurrentDay::cardAtPositionAfterMultipleShuffles(lines, 119315717514047, 101741582076661, 2020) << std::endl;
}
