#include "SensorReportAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int TUNING_FREQUENCY_X_COORDINATE_FACTOR = 4'000'000;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day15
{

SensorReportAnalyzer::SensorReportAnalyzer(const std::vector<CoordinatesPair> sensorAndBeaconPositions)
{
    for (const auto& sensorAndBeaconPosition : sensorAndBeaconPositions)
    {
        const auto& sensorPosition = sensorAndBeaconPosition.first;
        const auto& beaconPosition = sensorAndBeaconPosition.second;

        const int distanceX = std::abs(sensorPosition.first - beaconPosition.first);
        const int distanceY = std::abs(sensorPosition.second - beaconPosition.second);
        const int exclusionRadius = distanceX + distanceY;

        m_sensorPositionsAndExclusionRadiuses.emplace_back(sensorPosition, exclusionRadius);
    }
}

unsigned SensorReportAnalyzer::getNumPositionsThatCannotContainBeaconInSpecificRow(int y) const
{
    IntIntervalSet exclusionZone = getExclusionZoneInSpecificRow(y);

    unsigned numTotalElementsInExclusionZone = 0;

    for (auto exclusionZoneElementIter = exclusionZone.begin(); exclusionZoneElementIter != exclusionZone.end(); ++exclusionZoneElementIter)
    {
        const unsigned numElements = (exclusionZoneElementIter->upper() - 1) - exclusionZoneElementIter->lower();
        numTotalElementsInExclusionZone += numElements;
    }

    return numTotalElementsInExclusionZone;
}

int64_t SensorReportAnalyzer::getDistressBeaconTuningFrequency(int distressBeaconCoordinatesLowerBound, int distressBeaconCoordinatesUpperBound) const
{
    for (int y = distressBeaconCoordinatesLowerBound; y <= distressBeaconCoordinatesUpperBound; ++y)
    {
        IntIntervalSet exclusionZone = getExclusionZoneInSpecificRow(y);
        IntIntervalSet relevantExclusionZone = exclusionZone & IntIntervalSet{{distressBeaconCoordinatesLowerBound, distressBeaconCoordinatesUpperBound}};

        if (relevantExclusionZone.iterative_size() > 1)
        {
            const int x = relevantExclusionZone.begin()->upper();
            return TUNING_FREQUENCY_X_COORDINATE_FACTOR * static_cast<int64_t>(x) + y;
        }
    }

    throw std::runtime_error("Unable to find distress beacon");
}

IntIntervalSet SensorReportAnalyzer::getExclusionZoneInSpecificRow(int y) const
{
    IntIntervalSet exclusionZone;

    for (const auto& sensorPositionAndExclusionRadius : m_sensorPositionsAndExclusionRadiuses)
    {
        IntIntervalSet::interval_type excludedInterval = getExclusionIntervalForSensorInSpecificRow(sensorPositionAndExclusionRadius.first, sensorPositionAndExclusionRadius.second, y);
        exclusionZone.insert(std::move(excludedInterval));
    }

    return exclusionZone;
}

IntIntervalSet::interval_type SensorReportAnalyzer::getExclusionIntervalForSensorInSpecificRow(const Coordinates& sensorPosition, int exclusionRadius, int y)
{
    const int offsetY = std::abs(sensorPosition.second - y);
    const int remainingExtraRadius = exclusionRadius - offsetY;

    if (remainingExtraRadius < 0)
    {
        return IntIntervalSet::interval_type{};
    }

    return IntIntervalSet::interval_type{sensorPosition.first - remainingExtraRadius, sensorPosition.first + remainingExtraRadius + 1};
}

}
}
}
