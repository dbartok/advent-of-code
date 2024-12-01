#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day25
{

using MapRow = std::string;
using Map = std::vector<MapRow>;
using Coordinates = std::pair<int, int>;

class SeaCucumberMovementSimulator
{
public:
    SeaCucumberMovementSimulator(Map initialMap);

    void simulateUntilFirstStepWithoutAnyMovement();

    unsigned getNumSteps() const;

private:
    Map m_currentMap;
    Map m_nextMap;
    size_t m_width;
    size_t m_height;

    unsigned m_numSteps = 0;

    void advanceMovementForAllSeaCucumbers();
    void advanceMovementForSeaCucumberType(char seaCucumberType);
    void advanceMovementInNextMapForSeaCucumberTypeAt(char seaCucumberType, const Coordinates& coordinates);
    void swapPositionsInNextMap(const Coordinates& coordinates, const Coordinates& movementDestination);
    
    char getCurrentFieldTypeAt(const Coordinates& coordinates) const;
    Coordinates getMovementDestinationForSeaCucumberAt(const Coordinates& coordinates) const;
};

}
}
}
