#include "Day04-ReposeRecord.h"

#include "GuardDutyKeeper.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <chrono>
#include <sstream>
#include <iomanip>
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day04
{

const int SOME_VALID_YEAR_FOR_TIMESTAMP = 1970 - 1900;

struct Event
{
    Event(std::tm timestamp, std::string description) noexcept
        : timestamp{std::move(timestamp)}
        , description{std::move(description)}
    {

    }

    std::tm timestamp;
    std::string description;
};

// The year in the puzzle is 1518, which is before the POSIX Epoch
// So we're ignoring the year when parsing, and set it to some valid year instead
std::tm parseTimestampWithoutYear(const std::string& timestampString)
{
    const size_t yearEndPos = timestampString.find('-');
    std::string timeStampWithoutYearString = timestampString.substr(yearEndPos + 1);

    std::stringstream ss{timeStampWithoutYearString};
    std::tm tm = {};
    ss >> std::get_time(&tm, "%m-%d %H:%M");
    tm.tm_year = SOME_VALID_YEAR_FOR_TIMESTAMP;
    std::mktime(&tm);

    return tm;
}

std::vector<Event> parseEventsFromEventLines(const std::vector<std::string>& eventLines)
{
    std::vector<Event> events;

    for (const auto& line : eventLines)
    {
        std::vector<std::string> tokens;
        boost::algorithm::split(tokens, line, boost::is_any_of("]"), boost::token_compress_on);

        std::string timestampString = tokens[0];
        boost::trim_if(timestampString, boost::is_any_of("["));

        const std::tm tm = parseTimestampWithoutYear(timestampString);

        Event event{std::move(tm), std::move(tokens[1])};

        events.push_back(std::move(event));
    }

    return events;
}

std::vector<std::vector<Event>> getEventsForEachDay(std::vector<Event> &events)
{
    std::vector<std::vector<Event>> eventsForEachDay;

    std::vector<Event> eventsForADay;
    for (auto iter = events.begin(); iter != events.end(); ++iter)
    {
        eventsForADay.push_back(std::move(*iter));

        const auto nextIter = (iter + 1);

        // Next element signals that the current day is over
        if (nextIter == events.end() || nextIter->description.find("begins shift") != std::string::npos)
        {
            eventsForEachDay.push_back(std::move(eventsForADay));
            eventsForADay.clear();
        }
    }

    return eventsForEachDay;
}

GuardIDType parseGuardIDFromDescription(const std::string& description)
{
    std::regex guardIDRegex("#([0-9]+)");
    std::smatch matchResults;
    std::regex_search(description, matchResults, guardIDRegex);

    return boost::lexical_cast<unsigned>(matchResults[1]);
}

MinutesToBoolMap parseHourMapFromEvents(const std::vector<Event>& eventsForADay)
{
    MinutesToBoolMap hourMap{};

    int previousMinutePoint = 0;
    bool currentSleepingState = false;
    for (auto eventIter = eventsForADay.cbegin(); eventIter != eventsForADay.cend(); ++eventIter)
    {
        const int currentMinutePoint = eventIter->timestamp.tm_min;
        std::fill(hourMap.begin() + previousMinutePoint, hourMap.begin() + currentMinutePoint, currentSleepingState);

        // Sleeps and wakeups are in alternating order
        currentSleepingState = !currentSleepingState;
        previousMinutePoint = currentMinutePoint;
    }

    // No more events, fill up the rest of the hour with the current sleeping state
    std::fill(hourMap.begin() + previousMinutePoint, hourMap.end(), currentSleepingState);

    return hourMap;
}

GuardDutyKeeper parseGuardDutyKeeperFromEventsForEachDay(const std::vector<std::vector<Event>>& eventsForEachDay)
{
    GuardDutyKeeper guardDutyKeeper;

    for (const auto& eventsForADay : eventsForEachDay)
    {
        // Guard beginning shift is the first event of the day
        const GuardIDType guardID = parseGuardIDFromDescription(eventsForADay.front().description);

        // Discard first event, the rest is sleeps and wakeups
        std::vector<Event> sleepWakeupEvents{std::make_move_iterator(eventsForADay.begin() + 1), std::make_move_iterator(eventsForADay.end())};
        MinutesToBoolMap hourMap = parseHourMapFromEvents(sleepWakeupEvents);

        guardDutyKeeper.addDayForGuard(guardID, std::move(hourMap));
    }

    return guardDutyKeeper;
}

GuardDutyKeeper parseGuardDutyKeeperFromEventLines(const std::vector<std::string>& eventLines)
{
    std::vector<Event> events = parseEventsFromEventLines(eventLines);

    std::sort(events.begin(), events.end(), [](const Event& lhs, const Event& rhs) noexcept
              {
                  auto lts = lhs.timestamp;
                  auto rts = rhs.timestamp;

                  return std::difftime(std::mktime(&lts), std::mktime(&rts)) < 0;
              });

    std::vector<std::vector<Event>> eventsForEachDay = getEventsForEachDay(events);

    return parseGuardDutyKeeperFromEventsForEachDay(eventsForEachDay);
}

unsigned guardMostMinutesSleptTimesMinute(const std::vector<std::string>& eventLines)
{
    GuardDutyKeeper guardDutyKeeper = parseGuardDutyKeeperFromEventLines(eventLines);

    const GuardIDType mostSleptGuardID = guardDutyKeeper.getMostSleptGuardID();
    const unsigned mostSleptMinute = guardDutyKeeper.getMostFrequentlySleptMinute(mostSleptGuardID).first;

    return mostSleptGuardID * mostSleptMinute;
}

unsigned guardMostFrequentlyMinuteSleptTimesMinute(const std::vector<std::string>& eventLines)
{
    GuardDutyKeeper guardDutyKeeper = parseGuardDutyKeeperFromEventLines(eventLines);

    const GuardIDType mostFrequentlyMinuteSleptGuardID = guardDutyKeeper.getMostFrequentlySleptMinuteGlobalGuardID();
    const unsigned mostSleptMinute = guardDutyKeeper.getMostFrequentlySleptMinute(mostFrequentlyMinuteSleptGuardID).first;

    return mostFrequentlyMinuteSleptGuardID * mostSleptMinute;
}

}
}
}
