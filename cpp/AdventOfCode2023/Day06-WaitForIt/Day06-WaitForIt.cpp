#include "Day06-WaitForIt.h"

#include "Race.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day06
{

int64_t parseRaceDescriptionLineAsSingleRace(const std::string& raceDescriptionLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, raceDescriptionLine, boost::is_any_of(":"));

    std::string numberToken = tokens.at(1);
    numberToken.erase(std::remove_if(numberToken.begin(), numberToken.end(), [](const char c) {return std::isspace(c); }), numberToken.end());
    return std::stoll(numberToken);
}

std::vector<int64_t> parseRaceDescriptionLine(const std::string& raceDescriptionLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, raceDescriptionLine, boost::is_any_of(" :"), boost::token_compress_on);

    std::vector<int64_t> numbers;

    std::transform(tokens.cbegin() + 1, tokens.cend(), std::back_inserter(numbers), [](const auto& token)
                   {
                       return std::stoll(token);
                   });

    return numbers;
}

Race parseRaceDescriptionLinesAsSingleRace(const std::vector<std::string>& raceDescriptionLines)
{
    int64_t time = parseRaceDescriptionLineAsSingleRace(raceDescriptionLines.at(0));
    int64_t recordDistance = parseRaceDescriptionLineAsSingleRace(raceDescriptionLines.at(1));

    return {time, recordDistance};
}

std::vector<Race> parseRaceDescriptionLines(const std::vector<std::string>& raceDescriptionLines)
{
    const std::vector<int64_t> times = parseRaceDescriptionLine(raceDescriptionLines.at(0));
    const std::vector<int64_t> recordDistances = parseRaceDescriptionLine(raceDescriptionLines.at(1));

    std::vector<Race> races;

    for (size_t i = 0; i < times.size(); ++i)
    {
        races.emplace_back(times.at(i), recordDistances.at(i));
    }

    return races;
}

int64_t numWaysRecordCanBeBeatenMultipliedTogether(const std::vector<std::string>& raceDescriptionLines)
{
    std::vector<Race> races = parseRaceDescriptionLines(raceDescriptionLines);

    return std::accumulate(races.cbegin(), races.cend(), 1, [](int64_t acc, const auto& race)
                           {
                               return acc * race.getNumWaysToBeatRecord();
                           });
}

int64_t numWaysRecordCanBeBeatenSingleRace(const std::vector<std::string>& raceDescriptionLines)
{
    Race race = parseRaceDescriptionLinesAsSingleRace(raceDescriptionLines);

    return race.getNumWaysToBeatRecord();
}

}
}
}