#include "Day24-ArithmeticLogicUnit.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2021::Day24;

    std::cout << "First part: " << CurrentDay::largestModelNumberAcceptedByMonad() << std::endl;
    std::cout << "Second part: " << CurrentDay::smallestModelNumberAcceptedByMonad() << std::endl;
}
