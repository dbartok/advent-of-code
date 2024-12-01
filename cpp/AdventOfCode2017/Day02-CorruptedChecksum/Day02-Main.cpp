#include "Day02-CorruptedChecksum.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day02;

    std::fstream fileIn("input.txt");
    CurrentDay::RowsOfNumbers inputRows;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        CurrentDay::RowOfNumbers row;
        AdventOfCode::Utils::splitStringIntoTypedVector(lineBuffer, row, '\t');
        inputRows.push_back(std::move(row));
    }

    std::cout << "First part: " << CurrentDay::checkSumDiffSmallestLargest(inputRows) << std::endl;
    std::cout << "Second part: " << CurrentDay::sumEvenlyDivisbleValues(inputRows) << std::endl;
}
