#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_map>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day03
{

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct WireSection
{
    Direction direction;
    unsigned length;
};

struct Wire
{
    std::vector<WireSection> wireSections;
};

using WireID = unsigned;

struct FieldWireInfo
{
    std::unordered_set<WireID> wires;
    int numTotalWireSteps = 0;
};

class WirePlanter
{
public:
    WirePlanter(std::vector<Wire> wires);

    void plant();
    int getDistanceToClosestIntersection() const;
    int getCombinedWireStepsToClosestIntersection() const;

private:
    using Coordinates = std::pair<int, int>;

    std::vector<Wire> m_wires;

    std::unordered_map<Coordinates, FieldWireInfo, boost::hash<Coordinates>> m_coordinatesToWires;

    std::vector<Coordinates> getAllIntersectionCoordinates() const;

    static Coordinates getNeighborCoordinates(const Coordinates& coordinates, Direction direction);
};

}
}
}
