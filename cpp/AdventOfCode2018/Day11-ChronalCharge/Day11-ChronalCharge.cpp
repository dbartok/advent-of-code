#include "Day11-ChronalCharge.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day11
{

std::string highestPowerSmallSquareCoordinates(int gridSerialNumber)
{
    const FuelCellGrid fuelCellGrid{gridSerialNumber};

    const auto coordinates = fuelCellGrid.highestPowerSmallSquareCoordinates();

    return std::to_string(coordinates.first) + "," + std::to_string(coordinates.second);
}

std::string highestPowerSquareCoordinatesAndSize(int gridSerialNumber, size_t maxSize)
{
    const FuelCellGrid fuelCellGrid{gridSerialNumber};

    const auto square = fuelCellGrid.highestPowerSquare(maxSize);
    const auto& coordinates = square.coordinates;
    const size_t size = square.size;

    return std::to_string(coordinates.first) + "," + std::to_string(coordinates.second) + "," + std::to_string(size);
}

}
}
}
