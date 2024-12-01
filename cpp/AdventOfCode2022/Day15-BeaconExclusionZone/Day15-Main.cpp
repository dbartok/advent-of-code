#include "Day15-BeaconExclusionZone.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int FIRST_PART_Y = 2'000'000;
const int DISTRESS_BEACON_COORDINATES_LOWER_BOUND = 0;
const int DISTRESS_BEACON_COORDINATES_UPPER_BOUND = 4'000'000;

}

int main()
{
    namespace CurrentDay = AdventOfCode::Year2022::Day15;

    std::fstream fileIn("input.txt");

    std::string lineBuffer;
    std::vector<std::string> lines;
    while (std::getline(fileIn, lineBuffer))
    {
        lines.push_back(std::move(lineBuffer));
    }

    std::cout << "First part: " << CurrentDay::numPositionsThatCannotContainBeaconInSpecificRow(lines, FIRST_PART_Y) << std::endl;
    std::cout << "Second part: " << CurrentDay::distressBeaconTuningFrequency(lines, DISTRESS_BEACON_COORDINATES_LOWER_BOUND, DISTRESS_BEACON_COORDINATES_UPPER_BOUND) << std::endl;
}
