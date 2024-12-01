#include "Day24-BlizzardBasin.h"

#include "BlizzardPathfinder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

AdventOfCode::Year2022::Day24::Coordinates GAP_OFFSET{1, 0};

}

namespace
{

unsigned FIRST_PART_NUM_SEGMENTS = 1;
unsigned SECOND_PART_NUM_SEGMENTS = 3;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day24
{

BlizzardMap parseBlizzardMapLines(const std::vector<std::string>& blizzardMapLines)
{
    const unsigned width = blizzardMapLines.at(0).size();
    const unsigned height = blizzardMapLines.size();

    CoordinateToBlizzards xCoordinateToBlizzards;
    CoordinateToBlizzards yCoordinateToBlizzards;

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            switch (blizzardMapLines.at(j).at(i))
            {
                case '>':
                    yCoordinateToBlizzards[j].emplace_back(i, 1);
                    break;
                case '<':
                    yCoordinateToBlizzards[j].emplace_back(i, -1);
                    break;
                case 'v':
                    xCoordinateToBlizzards[i].emplace_back(j, 1);
                    break;
                case '^':
                    xCoordinateToBlizzards[i].emplace_back(j, -1);
                    break;
                default:
                    break;
            }
        }
    }

    Coordinates startPosition = GAP_OFFSET;
    Coordinates endPosition{width - 1 - GAP_OFFSET.first, height - 1 - GAP_OFFSET.second};

    return {width, height, std::move(startPosition), std::move(endPosition), std::move(xCoordinateToBlizzards), std::move(yCoordinateToBlizzards)};
}

unsigned fewestNumberOfMinutesForGivenNumberOfSegments(const std::vector<std::string>& blizzardMapLines, unsigned numSegments)
{
    BlizzardMap blizzardMap = parseBlizzardMapLines(blizzardMapLines);
    unsigned totalElapsedTime = 0;

    for (unsigned segment = 0; segment < numSegments; ++segment)
    {
        BlizzardPathfinder blizzardPathfinder{blizzardMap, totalElapsedTime};
        blizzardPathfinder.findShortestPath();
        totalElapsedTime += blizzardPathfinder.getMinTimeElapsedSinceStartToReachGoal();

        std::swap(blizzardMap.startPosition, blizzardMap.endPosition);
    }

    return totalElapsedTime;
}

unsigned fewestNumberOfMinutesToReachGoal(const std::vector<std::string>& blizzardMapLines)
{
    return fewestNumberOfMinutesForGivenNumberOfSegments(blizzardMapLines, 1);
}

unsigned fewestNumberOfMinutesToReachGoalAfterGoingBackForSnacks(const std::vector<std::string>& blizzardMapLines)
{
    return fewestNumberOfMinutesForGivenNumberOfSegments(blizzardMapLines, 3);
}

}
}
}