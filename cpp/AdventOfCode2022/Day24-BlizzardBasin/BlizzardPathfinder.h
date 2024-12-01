#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_map>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day24
{

struct Blizzard
{
    int initialOffset;
    int velocity;

    Blizzard(int initialOffset, int velocity)
        : initialOffset{initialOffset}
        , velocity{velocity}
    {

    }
};

using Blizzards = std::vector<Blizzard>;
using CoordinateToBlizzards = std::unordered_map<int, Blizzards>;
using Coordinates = std::pair<int, int>;

struct BlizzardMap
{
    unsigned width;
    unsigned height;
    Coordinates startPosition;
    Coordinates endPosition;
    CoordinateToBlizzards xCoordinateToBlizzards;
    CoordinateToBlizzards yCoordinateToBlizzards;
};

class BlizzardPathfinder
{
public:
    BlizzardPathfinder(BlizzardMap blizzardMap, unsigned startTime);

    void findShortestPath();

    unsigned getMinTimeElapsedSinceStartToReachGoal() const;

private:
    struct Node
    {
        Coordinates position;
        unsigned timeElapsed;
        unsigned remainingTimeLowerBound;

        bool operator==(const Node& other) const
        {
            return position == other.position && timeElapsed == other.timeElapsed;
        }

        Node(Coordinates position, unsigned timeElapsed, unsigned remainingTimeLowerBound)
            : position{std::move(position)}
            , timeElapsed{timeElapsed}
            , remainingTimeLowerBound{remainingTimeLowerBound}
        {

        }
    };

    struct NodeHash
    {
        size_t operator()(const Node& node) const
        {
            std::size_t seed = 0;

            boost::hash_combine(seed, node.position);
            boost::hash_combine(seed, node.timeElapsed);

            return seed;
        }
    };

    BlizzardMap m_blizzardMap;
    unsigned m_startTime;

    unsigned m_minTimeElapsedToReachGoal;

    unsigned getRemainingTimeLowerBound(const Coordinates& coordinates) const;
    std::vector<Node> getNeighborNodes(const Node& currentNode) const;
    bool isPositionFreeAtTime(const Coordinates& position, unsigned time) const;
    static bool isPositionBlizzardFreeAtTime(const CoordinateToBlizzards& coordinateToBlizzards, int blizzardMapKey, int positionToCheck, unsigned time, unsigned arrayLength);
    static int mod(int a, int b);
};

}
}
}
