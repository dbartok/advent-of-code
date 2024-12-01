#include "DonutMazeParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day20
{

DonutMazeParser::DonutMazeParser(std::vector<std::string> donutMazeLines)
    : m_map{std::move(donutMazeLines)}
{

}

void DonutMazeParser::parse()
{
    for (int j = 0; j < m_map.size(); ++j)
    {
        for (int i = 0; i < m_map.at(j).size(); ++i)
        {
            if (isPortalElement({i, j}))
            {
                processPortal({i, j});
            }
        }
    }
}

DonutMaze DonutMazeParser::getDonutMaze() const
{
    DonutMaze donutMaze;
    donutMaze.map = m_map;

    for (const auto& portalNameAndEndpoints : m_portalNameToEndpoints)
    {
        std::string portalName = portalNameAndEndpoints.first;
        std::vector<Coordinates> endpoints = portalNameAndEndpoints.second;
        if (portalName == "AA")
        {
            donutMaze.start = endpoints.front();
        }
        else if (portalName == "ZZ")
        {
            donutMaze.end = endpoints.front();
        }
        else
        {
            Coordinates source = endpoints.at(0);
            Coordinates destination = endpoints.at(1);
            donutMaze.portalToDestination[source] = destination;
            donutMaze.portalToDestination[destination] = source;
        }
    }

    return donutMaze;
}

void DonutMazeParser::processPortal(const Coordinates& firstLetterCoordinates)
{
    Coordinates secondLetterCoordinates = getSecondLetterCoordinates(firstLetterCoordinates);
    Coordinates connectedTileCoordinates = getConnectedTileCoordinates({firstLetterCoordinates, secondLetterCoordinates});

    std::string portalName = {atCoordinates(firstLetterCoordinates), atCoordinates(secondLetterCoordinates)};

    m_portalNameToEndpoints[portalName].push_back(connectedTileCoordinates);

    m_map.at(firstLetterCoordinates.second).at(firstLetterCoordinates.first) = ' ';
    m_map.at(secondLetterCoordinates.second).at(secondLetterCoordinates.first) = ' ';
}

Coordinates DonutMazeParser::getSecondLetterCoordinates(const Coordinates& firstLetterCoordinates) const
{
    Coordinates rightNeighbor{firstLetterCoordinates.first + 1, firstLetterCoordinates.second};
    if (isPortalElement(rightNeighbor))
    {
        return rightNeighbor;
    }

    Coordinates downNeighbor{firstLetterCoordinates.first, firstLetterCoordinates.second + 1};
    return downNeighbor;
}

Coordinates DonutMazeParser::getConnectedTileCoordinates(const std::vector<Coordinates>& portalCoordinates) const
{
    std::vector<Coordinates> candidateTileCoordinates;
    for (const auto& coord : portalCoordinates)
    {
        std::vector<Coordinates> neighborCoordinates = getNeighborCoordinates(coord);
        std::copy(neighborCoordinates.begin(), neighborCoordinates.end(), std::back_inserter(candidateTileCoordinates));
    }

    for (const auto& coords : candidateTileCoordinates)
    {
        if (isFreeTile(coords))
        {
            return coords;
        }
    }

    throw std::runtime_error("Cannot find connected tile");
}

std::vector<Coordinates> DonutMazeParser::getNeighborCoordinates(const Coordinates& coordinates) const
{
    std::vector<Coordinates> neighbors;
    neighbors.push_back({coordinates.first + 1, coordinates.second});
    neighbors.push_back({coordinates.first - 1, coordinates.second});
    neighbors.push_back({coordinates.first, coordinates.second + 1});
    neighbors.push_back({coordinates.first, coordinates.second - 1});
    return neighbors;
}

bool DonutMazeParser::isPortalElement(const Coordinates& coordinates) const
{
    return std::isalpha(atCoordinates(coordinates));
}

bool DonutMazeParser::isFreeTile(const Coordinates& coordinates) const
{
    return atCoordinates(coordinates) == '.';
}

char DonutMazeParser::atCoordinates(const Coordinates& coordinates) const
{
    if (coordinates.second < 0 || coordinates.second >= m_map.size() || coordinates.first < 0 || coordinates.first >= m_map.at(coordinates.second).size())
    {
        return '#';
    }

    return m_map.at(coordinates.second).at(coordinates.first);
}

}
}
}
