#pragma once

#include "FuelCellGrid.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
}

namespace AdventOfCode
{

std::string highestPowerSmallSquareCoordinates(int gridSerialNumber);
std::string highestPowerSquareCoordinatesAndSize(int gridSerialNumber, size_t maxSize = GRID_SIZE);

}
