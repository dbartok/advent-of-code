#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>

#include <vector>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day20
{

using MazeMap = std::vector<std::string>;
using Coordinates = std::pair<int, int>;

struct DonutMaze
{
    MazeMap map;
    Coordinates start;
    Coordinates end;
    std::unordered_map<Coordinates, Coordinates, boost::hash<Coordinates>> portalToDestination;
};

using PortalNameToEndpoints = std::unordered_map<std::string, std::vector<Coordinates>>;

class DonutMazeParser
{
public:
    DonutMazeParser(std::vector<std::string> donutMazeLines);

    void parse();

    DonutMaze getDonutMaze() const;

private:
    MazeMap m_map;
    PortalNameToEndpoints m_portalNameToEndpoints;

    void processPortal(const Coordinates& firstLetterCoordinates);

    Coordinates getSecondLetterCoordinates(const Coordinates& firstLetterCoordinates) const;
    Coordinates getConnectedTileCoordinates(const std::vector<Coordinates>& portalCoordinates) const;
    std::vector<Coordinates> getNeighborCoordinates(const Coordinates& coordinates) const;
    bool isPortalElement(const Coordinates& coordinates) const;
    bool isFreeTile(const Coordinates& coordinates) const;
    char atCoordinates(const Coordinates& coordinates) const;
};

}
}
}
