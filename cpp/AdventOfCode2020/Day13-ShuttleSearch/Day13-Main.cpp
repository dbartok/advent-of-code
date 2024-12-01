#include "Day13-ShuttleSearch.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2020::Day13;

    std::fstream fileIn("input.txt");

    int earliestDepartureTimestamp;
    fileIn >> earliestDepartureTimestamp;

    std::string scheduleDescriptionString;
    fileIn >> scheduleDescriptionString;

    std::cout << "First part: " << CurrentDay::earliestBusIDMultipliedByWaitTime(earliestDepartureTimestamp, scheduleDescriptionString) << std::endl;
    std::cout << "Second part: " << CurrentDay::earliestTimestampWithMatchingDepartures(scheduleDescriptionString) << std::endl;
}
