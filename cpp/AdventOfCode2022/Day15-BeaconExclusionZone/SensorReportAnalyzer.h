#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/icl/interval_set.hpp>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day15
{

using Coordinates = std::pair<int, int>;
using CoordinatesPair = std::pair<Coordinates, Coordinates>;
using IntIntervalSet = boost::icl::interval_set<int>;

class SensorReportAnalyzer
{
public:
    SensorReportAnalyzer(const std::vector<CoordinatesPair> sensorAndBeaconPositions);

    unsigned getNumPositionsThatCannotContainBeaconInSpecificRow(int y) const;
    int64_t getDistressBeaconTuningFrequency(int distressBeaconCoordinatesLowerBound, int distressBeaconCoordinatesUpperBound) const;

private:
    std::vector<std::pair<Coordinates, int>> m_sensorPositionsAndExclusionRadiuses;

    IntIntervalSet getExclusionZoneInSpecificRow(int y) const;

    static IntIntervalSet::interval_type getExclusionIntervalForSensorInSpecificRow(const Coordinates& sensorPosition, int exclusionRadius, int y);
};

}
}
}
