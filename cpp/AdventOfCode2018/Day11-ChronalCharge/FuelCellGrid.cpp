#include "FuelCellGrid.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day11
{

FuelCellSubSquare::FuelCellSubSquare() noexcept
    : coordinates{}
    , size{0}
    , powerLevel{std::numeric_limits<int>::min()}
{

}

FuelCellSubSquare::FuelCellSubSquare(Coordinates coordinates, size_t size, int powerLevel) noexcept
    : coordinates{std::move(coordinates)}
    , size{size}
    , powerLevel{powerLevel}
{

}

bool FuelCellSubSquare::operator<(const FuelCellSubSquare& other) const noexcept
{
    return powerLevel < other.powerLevel;
}

bool FuelCellSubSquare::operator>(const FuelCellSubSquare& other) const noexcept
{
    return powerLevel > other.powerLevel;
}

FuelCellGrid::FuelCellGrid(int serialNumber) noexcept
    : m_serialNumber{serialNumber}
{

}

Coordinates FuelCellGrid::highestPowerSmallSquareCoordinates() const noexcept
{
    return highestPowerGivenSizeSubSquare(SMALL_SQUARE_SIZE).coordinates;
}

FuelCellSubSquare FuelCellGrid::highestPowerSquare(size_t maxSize) const
{
    FuelCellSubSquare maxSubSquare;

    for (size_t currentSize = 1; currentSize <= maxSize; ++currentSize)
    {
        const auto currentSubSquare = highestPowerGivenSizeSubSquare(currentSize);
        maxSubSquare = std::max(maxSubSquare, currentSubSquare);
    }

    return maxSubSquare;
}

int FuelCellGrid::valueAt(const Coordinates& coordinates) const noexcept
{
    const int rackID = coordinates.first + 10;

    int powerLevel = rackID * coordinates.second;
    powerLevel += m_serialNumber;
    powerLevel *= rackID;

    const int hundredsDigit = (powerLevel / 100) % 10;
    return hundredsDigit - 5;
}

int FuelCellGrid::getPowerLevelAt(const Coordinates& coordinates, size_t squareSize) const noexcept
{
    int powerLevel = 0;

    for (size_t i = coordinates.first; i < coordinates.first + squareSize; ++i)
    {
        for (size_t j = coordinates.second; j < coordinates.second + squareSize; ++j)
        {
            powerLevel += valueAt({i, j});
        }
    }

    return powerLevel;
}

FuelCellSubSquare FuelCellGrid::highestPowerGivenSizeSubSquare(size_t squareSize) const noexcept
{
    Coordinates maxCoordinates;
    int maxPowerLevel = std::numeric_limits<int>::min();
    const size_t topLeftCornerCandidatesSize = GRID_SIZE - squareSize;

    for (size_t i = 0; i < topLeftCornerCandidatesSize; ++i)
    {
        for (size_t j = 0; j < topLeftCornerCandidatesSize; ++j)
        {
            const Coordinates currentCoordinates{i, j};
            const int currentPowerLevel = getPowerLevelAt(currentCoordinates, squareSize);

            if (currentPowerLevel > maxPowerLevel)
            {
                maxPowerLevel = currentPowerLevel;
                maxCoordinates = currentCoordinates;
            }
        }
    }

    return FuelCellSubSquare{std::move(maxCoordinates), squareSize, maxPowerLevel};
}

}
}
}
