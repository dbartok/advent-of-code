#include "Day15-BeaconExclusionZone.h"

#include "SensorReportAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day15
{

CoordinatesPair parseSensorAndBeaconPositionLine(const std::string& sensorAndBeaconPositionLine)
{
    const std::regex sensorAndBeaconPositionLineRegex(R"(Sensor at x=(-?[0-9]+), y=(-?[0-9]+): closest beacon is at x=(-?[0-9]+), y=(-?[0-9]+))");
    std::smatch sensorAndBeaconPositionLineMatch;

    std::regex_match(sensorAndBeaconPositionLine, sensorAndBeaconPositionLineMatch, sensorAndBeaconPositionLineRegex);

    const int sensorX = std::stoi(sensorAndBeaconPositionLineMatch[1]);
    const int sensorY = std::stoi(sensorAndBeaconPositionLineMatch[2]);
    const int beaconX = std::stoi(sensorAndBeaconPositionLineMatch[3]);
    const int beaconY = std::stoi(sensorAndBeaconPositionLineMatch[4]);

    return {{sensorX, sensorY}, {beaconX, beaconY}};
}

std::vector<CoordinatesPair> parseSensorAndBeaconPositionLines(const std::vector<std::string>& sensorAndBeaconPositionLines)
{
    std::vector<CoordinatesPair> sensorAndBeaconPositions;

    for (const auto& sensorAndBeaconPositionLine : sensorAndBeaconPositionLines)
    {
        CoordinatesPair sensorAndBeaconPosition = parseSensorAndBeaconPositionLine(sensorAndBeaconPositionLine);
        sensorAndBeaconPositions.push_back(std::move(sensorAndBeaconPosition));
    }

    return sensorAndBeaconPositions;
}

unsigned numPositionsThatCannotContainBeaconInSpecificRow(const std::vector<std::string>& sensorAndBeaconPositionLines, int y)
{
    std::vector<CoordinatesPair> sensorAndBeaconPositions = parseSensorAndBeaconPositionLines(sensorAndBeaconPositionLines);

    SensorReportAnalyzer sensorReportAnalyzer{std::move(sensorAndBeaconPositions)};

    return sensorReportAnalyzer.getNumPositionsThatCannotContainBeaconInSpecificRow(y);
}

int64_t distressBeaconTuningFrequency(const std::vector<std::string>& sensorAndBeaconPositionLines, int distressBeaconCoordinatesLowerBound, int distressBeaconCoordinatesUpperBound)
{
    std::vector<CoordinatesPair> sensorAndBeaconPositions = parseSensorAndBeaconPositionLines(sensorAndBeaconPositionLines);

    SensorReportAnalyzer sensorReportAnalyzer{std::move(sensorAndBeaconPositions)};

    return sensorReportAnalyzer.getDistressBeaconTuningFrequency(distressBeaconCoordinatesLowerBound, distressBeaconCoordinatesUpperBound);
}

}
}
}