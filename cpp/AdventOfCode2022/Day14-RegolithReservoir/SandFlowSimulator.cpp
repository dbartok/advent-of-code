#include "SandFlowSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <iterator>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const AdventOfCode::Year2022::Day14::Coordinates SAND_START_COORDINATES = {500, 0};

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day14
{

SandFlowSimulator::SandFlowSimulator(CoordinatesSet allRockCoordinates)
    : m_allOccupiedCoordinates{std::move(allRockCoordinates)}
{

}

void SandFlowSimulator::simulate()
{
    while (true)
    {
        if (!trySettleNextSandParticle())
        {
            break;
        }
        ++m_numSettledUnits;
    }
}

unsigned SandFlowSimulator::getNumSettledUnits() const
{
    return m_numSettledUnits;
}

bool SandFlowSimulator::trySettleNextSandParticle()
{
    // Source blocked
    if (m_allOccupiedCoordinates.find(SAND_START_COORDINATES) != m_allOccupiedCoordinates.cend())
    {
        return false;
    }

    Coordinates currentSandCoordinates = SAND_START_COORDINATES;

    while (true)
    {
        boost::optional<Coordinates> nextSandCoordinates = getNextSandCoordinates(currentSandCoordinates);

        // Sand particle has settled
        if (!nextSandCoordinates)
        {
            m_allOccupiedCoordinates.insert(currentSandCoordinates);
            return true;
        }
        // Sand particle will never settle
        else if (currentSandCoordinates.second > SIMULATION_BOUNDARY_COORDINATE)
        {
            return false;
        }
        // Move sand particle to next position
        else
        {
            currentSandCoordinates = nextSandCoordinates.get();
        }
    }
}

boost::optional<Coordinates> SandFlowSimulator::getNextSandCoordinates(const Coordinates& currentCoordinates) const
{
    std::vector<Coordinates> nextCoordinatesInOrderOfPreference =
    {
        {currentCoordinates.first, currentCoordinates.second + 1}, // Down
        {currentCoordinates.first - 1, currentCoordinates.second + 1}, // Down-left
        {currentCoordinates.first + 1, currentCoordinates.second + 1}, // Down-right
    };

    for (const auto& nextCoordinates : nextCoordinatesInOrderOfPreference)
    {
        if (m_allOccupiedCoordinates.find(nextCoordinates) == m_allOccupiedCoordinates.cend())
        {
            return nextCoordinates;
        }
    }

    return boost::none;
}

}
}
}
