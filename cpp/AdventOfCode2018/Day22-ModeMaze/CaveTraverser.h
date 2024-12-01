#pragma once

#include "CaveMap.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day22
{

enum class Equipment
{
    CLIMBING_GEAR,
    NOTHING,
    TORCH,
};

struct Node
{
    Coordinates coordinates;
    Equipment equipment;
    unsigned gScore;
    unsigned hScore;

    Node(Coordinates coordinates, Equipment equipment, unsigned gScore, unsigned hScore)
        : coordinates{std::move(coordinates)}
        , equipment{std::move(equipment)}
        , gScore{gScore}
        , hScore{hScore}
    {

    }

    bool operator==(const Node& other) const
    {
        return coordinates == other.coordinates && equipment == other.equipment;
    }
};

struct NodeHash
{
    size_t operator()(const Node& node) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, node.coordinates);
        boost::hash_combine(seed, node.equipment);

        return seed;
    }
};

class CaveTraverser
{
public:
    CaveTraverser(CaveMap caveMap);

    void traverse();

    unsigned getLowestCostToTarget() const;

private:
    const Coordinates START_COORDINATES = {0, 0};
    const unsigned EQUIPMENT_CHANGE_COST = 7;

    CaveMap m_caveMap;

    unsigned m_lowestCostToTarget = std::numeric_limits<unsigned>::max();

    std::vector<Node> getAdjacentNodes(const Node& node);

    std::vector<Coordinates> getAllNeighborCoordinates(const Coordinates& coordinates);
    Equipment getOtherValidEquipment(const Node& node);

    static unsigned heuristicCostEstimate(const Coordinates& start, const Coordinates& target);
    static bool isEquipmentCompatibleWithRiskLevel(Equipment equipment, unsigned riskLevel);
};

}
}
}
