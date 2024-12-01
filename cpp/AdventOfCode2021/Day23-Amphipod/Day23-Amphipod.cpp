#include "Day23-Amphipod.h"

#include "AmphipodOrganizer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char WALL_CHAR = '#';
const std::vector<std::string> EXTRA_LINES_PART_TWO =
{
    "  #D#C#B#A#",
    "  #D#B#A#C#"
};
const size_t EXTRA_LINES_INSERTION_OFFSET_PART_TWO = 3;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day23
{

Map parseInitialPositionsLines(const std::vector<std::string>& initialPositionsLines)
{
    Map map = Map(initialPositionsLines.size(), MapRow(initialPositionsLines.at(0).size(), WALL_CHAR));

    for (int j = 0; j < initialPositionsLines.size(); ++j)
    {
        for (int i = 0; i < initialPositionsLines.at(j).size(); ++i)
        {
            const char initialPositionsChar = initialPositionsLines.at(j).at(i);
            if (initialPositionsChar != ' ')
            {
                map.at(j).at(i) = initialPositionsChar;
            }
        }
    }

    return map;
}

std::vector<std::string> getExtendedLines(const std::vector<std::string>& initialPositionsLines)
{
    auto extendedLines{initialPositionsLines};
    extendedLines.insert(extendedLines.begin() + EXTRA_LINES_INSERTION_OFFSET_PART_TWO, EXTRA_LINES_PART_TWO.cbegin(), EXTRA_LINES_PART_TWO.cend());
    return extendedLines;
}

unsigned leastEnergyRequiredToOrganize(const std::vector<std::string>& initialPositionsLines)
{
    Map map = parseInitialPositionsLines(initialPositionsLines);
    AmphipodOrganizer organizer{std::move(map)};
    organizer.organize();
    return organizer.getMinEnergyUsed();
}

unsigned leastEnergyRequiredToOrganizeExtendedMap(const std::vector<std::string>& initialPositionsLines)
{
    std::vector<std::string> extendedLines = getExtendedLines(initialPositionsLines);
    Map map = parseInitialPositionsLines(std::move(extendedLines));
    AmphipodOrganizer organizer{std::move(map)};
    organizer.organize();
    return organizer.getMinEnergyUsed();
}

}
}
}