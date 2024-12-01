#include "Day05-SunnyWithAsteroids.h"

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
    namespace CurrentDay = AdventOfCode::Year2019::Day05;

    std::fstream fileIn("input.txt");
    const std::string intcodeProgramCommaSeparated
    {
        (std::istreambuf_iterator<char>(fileIn)),
        (std::istreambuf_iterator<char>())
    };

    std::vector<CurrentDay::IntcodeNumberType> intcodeProgram;
    AdventOfCode::Utils::splitStringIntoTypedVector(intcodeProgramCommaSeparated, intcodeProgram, ',');

    std::cout << "First part: " << CurrentDay::diagnosticCodeProducedByProgram(intcodeProgram, 1) << std::endl;
    std::cout << "Second part: " << CurrentDay::diagnosticCodeProducedByProgram(intcodeProgram, 5) << std::endl;
}
