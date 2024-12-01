#include "Day17-Spinlock.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day17;

    std::fstream fileIn("input.txt");
    unsigned inputStepsForward;

    fileIn >> inputStepsForward;

    std::cout << "First part: " << CurrentDay::valueAfterLastWritten(inputStepsForward) << std::endl;
    std::cout << "Second part: " << CurrentDay::valueAfterZeroAfterManyInsertions(inputStepsForward) << std::endl;
}
