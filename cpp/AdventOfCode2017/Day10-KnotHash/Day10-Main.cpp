#include "Day10-KnotHash.h"

#include "KnotHasher.h"
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
    namespace CurrentDay = AdventOfCode::Year2017::Day10;

    std::fstream fileIn("input.txt");

    std::string inputLengthsString;
    std::getline(fileIn, inputLengthsString);

    std::vector<unsigned> inputLengths;
    AdventOfCode::Utils::splitStringIntoTypedVector(inputLengthsString, inputLengths, ',');

    std::cout << "First part: " << CurrentDay::firstTwoMultipliedAfterKnotting(CurrentDay::KnotHasher::STANDARD_LIST_SIZE, inputLengths) << std::endl;
    std::cout << "Second part: " << CurrentDay::knotHashDenseString(inputLengthsString) << std::endl;
}
