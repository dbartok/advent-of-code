#include "Day16-FlawedFrequencyTransmission.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2019::Day16;

    std::fstream fileIn("input.txt");
    std::string signalString
    {
        (std::istreambuf_iterator<char>(fileIn)),
        (std::istreambuf_iterator<char>())
    };

    signalString.erase(std::remove(signalString.begin(), signalString.end(), '\n'), signalString.end());

    std::cout << "First part: " << CurrentDay::firstEightDigitsOfFinalOutput(signalString) << std::endl;
    std::cout << "Second part: " << CurrentDay::messageInFinalOutputForRealSignal(signalString) << std::endl;
}
