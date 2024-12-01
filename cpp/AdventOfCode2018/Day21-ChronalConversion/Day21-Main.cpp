#include "Day21-ChronalConversion.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2018::Day21;

    std::cout << "First part: " << CurrentDay::lowestValueForFirstRegisterFewestInstructions() << std::endl;
    std::cout << "Second part: " << CurrentDay::lowestValueForFirstRegisterMostInstructions() << std::endl;
}
