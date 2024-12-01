#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <utility>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const size_t GRID_SIZE = 300;
const size_t SMALL_SQUARE_SIZE = 3;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day11
{

using Coordinates = std::pair<unsigned, unsigned>;

struct FuelCellSubSquare
{
    Coordinates coordinates;
    size_t size;
    int powerLevel;

    FuelCellSubSquare() noexcept;
    FuelCellSubSquare(Coordinates coordinates, size_t size, int powerLevel) noexcept;

    bool operator<(const FuelCellSubSquare& other) const noexcept;
    bool operator>(const FuelCellSubSquare& other) const noexcept;
};

class FuelCellGrid
{
public:
    FuelCellGrid(int serialNumber) noexcept;

    Coordinates highestPowerSmallSquareCoordinates() const noexcept;
    FuelCellSubSquare highestPowerSquare(size_t maxSize) const;

private:
    int m_serialNumber;

    FuelCellSubSquare highestPowerGivenSizeSubSquare(size_t squareSize) const noexcept;

    int valueAt(const Coordinates& coordinates) const noexcept;
    int getPowerLevelAt(const Coordinates& coordinates, size_t squareSize) const noexcept;
};

}
}
}
