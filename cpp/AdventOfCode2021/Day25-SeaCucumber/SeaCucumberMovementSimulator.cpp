#include "SeaCucumberMovementSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

char RIGHT_FACING_SEA_CUCUMBER = '>';
char DOWN_FACING_SEA_SUCUMBER = 'v';
char EMPTY_FIELD = '.';

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day25
{

SeaCucumberMovementSimulator::SeaCucumberMovementSimulator(Map initialMap)
    : m_currentMap{std::move(initialMap)}
    , m_nextMap{m_currentMap}
    , m_width{m_currentMap.at(0).size()}
    , m_height{m_currentMap.size()}
{

}

void SeaCucumberMovementSimulator::simulateUntilFirstStepWithoutAnyMovement()
{
    Map previousMap{};
    while (previousMap != m_currentMap)
    {
        previousMap = m_currentMap;
        ++m_numSteps;
        advanceMovementForAllSeaCucumbers();
    }
}

unsigned SeaCucumberMovementSimulator::getNumSteps() const
{
    return m_numSteps;
}

void SeaCucumberMovementSimulator::advanceMovementForAllSeaCucumbers()
{
    advanceMovementForSeaCucumberType(RIGHT_FACING_SEA_CUCUMBER);
    advanceMovementForSeaCucumberType(DOWN_FACING_SEA_SUCUMBER);
}

void SeaCucumberMovementSimulator::advanceMovementForSeaCucumberType(char seaCucumberType)
{
    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            advanceMovementInNextMapForSeaCucumberTypeAt(seaCucumberType, {i, j});
        }
    }

    m_currentMap = m_nextMap;
}

void SeaCucumberMovementSimulator::advanceMovementInNextMapForSeaCucumberTypeAt(char seaCucumberType, const Coordinates& coordinates)
{
    if (getCurrentFieldTypeAt(coordinates) != seaCucumberType)
    {
        return;
    }

    const Coordinates movementDestination = getMovementDestinationForSeaCucumberAt(coordinates);

    if (getCurrentFieldTypeAt(movementDestination) == EMPTY_FIELD)
    {
        swapPositionsInNextMap(coordinates, movementDestination);
    }
}

void SeaCucumberMovementSimulator::swapPositionsInNextMap(const Coordinates& coordinates, const Coordinates& movementDestination)
{
    std::swap(m_nextMap.at(coordinates.second).at(coordinates.first), m_nextMap.at(movementDestination.second).at(movementDestination.first));
}

char SeaCucumberMovementSimulator::getCurrentFieldTypeAt(const Coordinates& coordinates) const
{
    return m_currentMap.at(coordinates.second).at(coordinates.first);
}

Coordinates SeaCucumberMovementSimulator::getMovementDestinationForSeaCucumberAt(const Coordinates& coordinates) const
{
    const char seaCucumberType = getCurrentFieldTypeAt(coordinates);

    if (seaCucumberType == RIGHT_FACING_SEA_CUCUMBER)
    {
        return {(coordinates.first + 1) % m_width, coordinates.second};
    }
    else if (seaCucumberType == DOWN_FACING_SEA_SUCUMBER)
    {
        return {coordinates.first, (coordinates.second + 1) % m_height};
    }
    else
    {
        throw std::runtime_error("Invalid sea cucumber type: " + std::string{seaCucumberType});
    }
}

}
}
}
