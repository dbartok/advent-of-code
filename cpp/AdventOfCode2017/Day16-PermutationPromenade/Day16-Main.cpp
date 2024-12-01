#include "Day16-PermutationPromenade.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day16;

    std::fstream fileIn("input.txt");
    std::string commaSeparatedDanceMoves;
    std::getline(fileIn, commaSeparatedDanceMoves);

    std::vector<std::string> inputDanceMovesStrings;
    boost::split(inputDanceMovesStrings, commaSeparatedDanceMoves, boost::is_any_of(","));

    std::cout << "First part: " << CurrentDay::orderAfterDanceMovesSingleRepetition(inputDanceMovesStrings) << std::endl;
    std::cout << "Second part: " << CurrentDay::orderAfterDanceMovesRepetitions(inputDanceMovesStrings) << std::endl;
}
