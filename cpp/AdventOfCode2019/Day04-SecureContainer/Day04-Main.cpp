#include "Day04-SecureContainer.h"

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
    namespace CurrentDay = AdventOfCode::Year2019::Day04;

    std::fstream fileIn("input.txt");
    const std::string rangeHyphenSeparated
    {
        (std::istreambuf_iterator<char>(fileIn)),
        (std::istreambuf_iterator<char>())
    };

    std::vector<int> rangeBounds;
    AdventOfCode::Utils::splitStringIntoTypedVector(rangeHyphenSeparated, rangeBounds, '-');

    if (rangeBounds.size() != 2)
    {
        throw std::runtime_error("Invalid input");
    }

    std::cout << "First part: " << CurrentDay::numDifferentValidPasswordsSimple(rangeBounds.at(0), rangeBounds.at(1)) << std::endl;
    std::cout << "Second part: " << CurrentDay::numDifferentValidPasswordsLargerGroupIsNotMatching(rangeBounds.at(0), rangeBounds.at(1)) << std::endl;
}
