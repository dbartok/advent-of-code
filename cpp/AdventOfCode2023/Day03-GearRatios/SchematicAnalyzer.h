#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day03
{

using Coordinates = std::pair<int, int>;

class SchematicAnalyzer
{
public:
    SchematicAnalyzer(std::vector<std::string> schematic);

    int getSumOfAllPartNumbers() const;
    int getSumOfAllGearRatios() const;

private:
    const std::vector<std::string> m_schematic;
    const size_t m_width;
    const size_t m_height;

    bool isStartOfPartNumber(const Coordinates& coordinates) const;
    bool isGear(const Coordinates& coordinates) const;
    int getPartNumber(const Coordinates& numberStartCoordinates) const;
    int getGearRatio(const Coordinates& coordinates) const;
    bool isStartOfNumber(const Coordinates& coordinates) const;
    bool isNumberAdjacentToSymbol(const Coordinates& numberStartCoordinates) const;
    std::vector<int> getAdjacentNumbers(const Coordinates& centerCoordinates) const;
    std::vector<Coordinates> getAllDigitCoordinatesForNumber(const Coordinates& numberStartCoordinates) const;
    bool isPositionAdjacentToSymbol(const Coordinates& coordinates) const;
    std::vector<Coordinates> getAllNeighborCoordinates(const Coordinates& coordinates) const;
    char getValueAt(const Coordinates& coordinates) const;
};

}
}
}
