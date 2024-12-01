#include "Day11-SeatingSystem.h"

#include "SeatingSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day11
{

int numOccupiedSeatsWithAdjacencyRules(std::vector<std::string> seatLayoutLines)
{
    SeatingSimulator seatSimulator{std::move(seatLayoutLines), 1, 4};
    seatSimulator.simulateUntilStable();
    return seatSimulator.getNumOccupiedSeats();
}

int numOccupiedSeatsWithVisibilityRules(std::vector<std::string> seatLayoutLines)
{
    SeatingSimulator seatSimulator{std::move(seatLayoutLines), std::numeric_limits<size_t>::max(), 5};
    seatSimulator.simulateUntilStable();
    return seatSimulator.getNumOccupiedSeats();
}

}
}
}
