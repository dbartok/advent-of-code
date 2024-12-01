#pragma once

#include "CoordinatesToNeighborCoordinates.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day20
{

class RoomLayoutRegexParser
{
public:
    RoomLayoutRegexParser(std::string roomLayoutRegex);

    void parse();

    const CoordinatesToNeighborCoordinates& getLayoutMap() const;

private:
    std::string m_roomLayoutRegex;
    CoordinatesToNeighborCoordinates m_layoutMap;

    Coordinates getNeighborCoordinates(const Coordinates& coordinates, char neighborDirection);
};

}
}
}
