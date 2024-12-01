#include "RoomLayoutRegexParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stack>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day20
{

RoomLayoutRegexParser::RoomLayoutRegexParser(std::string roomLayoutRegex)
    : m_roomLayoutRegex{std::move(roomLayoutRegex)}
    , m_layoutMap{}
{

}

void RoomLayoutRegexParser::parse()
{
    Coordinates currentlyParsedCoordinates{0, 0};
    m_layoutMap.emplace(currentlyParsedCoordinates, CoordinatesSet{});
    std::stack<Coordinates> backtrackStack;

    for (size_t i = 1; i < m_roomLayoutRegex.length() - 1; ++i)
    {
        char currentChar = m_roomLayoutRegex[i];
        if (currentChar == '(')
        {
            backtrackStack.push(currentlyParsedCoordinates);
        }
        else if (currentChar == ')')
        {
            currentlyParsedCoordinates = backtrackStack.top();
            backtrackStack.pop();
        }
        else if (currentChar == '|')
        {
            currentlyParsedCoordinates = backtrackStack.top();
        }
        else
        {
            Coordinates neighborCoordinates = getNeighborCoordinates(currentlyParsedCoordinates, currentChar);
            m_layoutMap[currentlyParsedCoordinates].insert(std::move(neighborCoordinates));

            currentlyParsedCoordinates = neighborCoordinates;
        }
    }
}

const CoordinatesToNeighborCoordinates& RoomLayoutRegexParser::getLayoutMap() const
{
    return m_layoutMap;
}

Coordinates RoomLayoutRegexParser::getNeighborCoordinates(const Coordinates& coordinates, char neighborDirection)
{
    Coordinates neighborCoordinates{coordinates};

    switch (neighborDirection)
    {
        case 'N':
            neighborCoordinates.first -= 1;
            break;

        case 'S':
            neighborCoordinates.first += 1;
            break;

        case 'W':
            neighborCoordinates.second -= 1;
            break;

        case 'E':
            neighborCoordinates.second += 1;
            break;
    }

    return neighborCoordinates;
}

}
}
}
