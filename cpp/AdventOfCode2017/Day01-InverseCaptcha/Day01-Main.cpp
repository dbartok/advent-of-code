#include "Day01-InverseCaptcha.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day01;

    std::fstream fileIn("input.txt");
    std::string digitsString;

    fileIn >> digitsString;

    std::cout << "First part: " << CurrentDay::sumOfDigitsMatchNextDigit(digitsString) << std::endl;
    std::cout << "Second part: " << CurrentDay::sumOfDigitsMatchHalfwayRoundDigit(digitsString) << std::endl;
}
