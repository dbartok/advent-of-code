#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day17
{

using Coordinates = std::pair<int, int>;
using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct RobotCameraView
{
    Coordinates robotPosition;
    Direction robotDirection;
    CoordinatesSet scaffolds;
};

class ScaffoldAnalyzer
{
public:
    ScaffoldAnalyzer(RobotCameraView robotCameraView);

    void traverse();

    int getSumOfAlignmentParameters() const;
    std::vector<std::string> getJourneySteps() const;

private:
    RobotCameraView m_robotCameraView;

    std::vector<std::string> m_journeySteps;
    int m_stepsInStraightLine = 0;

    void turnIfNeeded();
    void turnLeft();
    void stepForward();

    std::vector<Coordinates> getNeighborScaffolds(const Coordinates& coordinates) const;
    bool isForwardPathObstructed() const;
    Coordinates getCoordinatesInFront() const;
};

}
}
}
