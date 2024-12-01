#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <set>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day15
{

using RiskLevelRow = std::vector<int>;
using RiskLevelMap = std::vector<RiskLevelRow>;

using Coordinates = std::pair<int, int>;

struct Node
{
    Coordinates coordinates;
    int riskLevel;
    int bestPathCostSoFar;
};

struct NodePtrCostCmp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        if (lhs->bestPathCostSoFar < rhs->bestPathCostSoFar)
        {
            return true;
        }

        if (lhs->bestPathCostSoFar > rhs->bestPathCostSoFar)
        {
            return false;
        }

        return lhs < rhs;
    }
};

class CaveTraverser
{
public:
    CaveTraverser(const RiskLevelMap& riskLevelMap);

    void traverse();

    int getMinRiskLevel() const;

private:
    std::unordered_map<Coordinates, Node, boost::hash<Coordinates>> m_coordinatesToNode;
    size_t m_width;
    size_t m_height;

    std::set<Node*, NodePtrCostCmp> m_activeNodePtrs;

    int m_MinRiskLevel = std::numeric_limits<int>::max();

    std::vector<Coordinates> getAllNeighborCoordinates(const Coordinates& baseCoordinates) const;
    bool isInBounds(const Coordinates& coordinates) const;
    bool isDestination(const Coordinates& coordinates) const;
};

}
}
}
