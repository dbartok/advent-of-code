#include "Day23-CategorySix.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2019::Day23;

    std::fstream fileIn("input.txt");
    const std::string intcodeProgramCommaSeparated
    {
        (std::istreambuf_iterator<char>(fileIn)),
        (std::istreambuf_iterator<char>())
    };

    std::vector<CurrentDay::IntcodeNumberType> intcodeProgram;
    AdventOfCode::Utils::splitStringIntoTypedVector(intcodeProgramCommaSeparated, intcodeProgram, ',');

    std::cout << "First part: " << CurrentDay::secondPartOfFirstPacketAtSpecialAddress(intcodeProgram) << std::endl;
    std::cout << "Second part: " << CurrentDay::secondPartOfFirstDuplicateMessageByNat(intcodeProgram) << std::endl;
}
