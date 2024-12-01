#include "Day13-ShuttleSearch.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <vector>
#include <cmath>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day13
{

struct BusDeparture
{
    int busID;
    int offset;
};

std::vector<BusDeparture> parseScheduleDescription(const std::string& scheduleDescriptionString)
{
    std::vector<std::string> tokens;
    boost::split(tokens, scheduleDescriptionString, boost::is_any_of(","));

    std::vector<BusDeparture> busDepartures;
    for (int i = 0; i < tokens.size(); ++i)
    {
        if (tokens.at(i) == "x")
        {
            continue;
        }
        const int busID = std::stoi(tokens.at(i));
        const int offset = i % busID;
        BusDeparture busDeparture{busID, offset};
        busDepartures.push_back(std::move(busDeparture));
    }

    return busDepartures;
}

int64_t getWaitTime(int64_t earliestDepartureTimestamp, int busID)
{
    int64_t earliestDepartureTimeViaThisBus = (earliestDepartureTimestamp / busID) * busID;
    if (earliestDepartureTimeViaThisBus < earliestDepartureTimestamp)
    {
        earliestDepartureTimeViaThisBus += busID;
    }
    return earliestDepartureTimeViaThisBus - earliestDepartureTimestamp;
}

int earliestBusIDMultipliedByWaitTime(int earliestDepartureTimestamp, const std::string& scheduleDescriptionString)
{
    std::vector<BusDeparture> busDepartures = parseScheduleDescription(scheduleDescriptionString);

    const auto minWaitTimeBusDepartureIter = std::min_element(busDepartures.cbegin(), busDepartures.cend(), [earliestDepartureTimestamp](const auto& lhs, const auto& rhs)
                                                              {
                                                                  return getWaitTime(earliestDepartureTimestamp, lhs.busID) < getWaitTime(earliestDepartureTimestamp, rhs.busID);
                                                              });

    const int minWaitTimeBusID = minWaitTimeBusDepartureIter->busID;

    return getWaitTime(earliestDepartureTimestamp, minWaitTimeBusID) * minWaitTimeBusID;
}

int64_t earliestTimestampWithMatchingDepartures(const std::string& scheduleDescriptionString)
{
    std::vector<BusDeparture> busDepartures = parseScheduleDescription(scheduleDescriptionString);

    int64_t delta = 1;
    int64_t candidate = 0;

    for (const auto& busDeparture : busDepartures)
    {
        const int busID = busDeparture.busID;
        const int offset = busDeparture.offset;
        while (getWaitTime(candidate, busID) != offset)
        {
            candidate += delta;
        }
        delta *= busID;
    }

    return candidate;
}

}
}
}
