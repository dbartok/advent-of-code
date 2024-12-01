#include "ScaffoldAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day17
{

ScaffoldAnalyzer::ScaffoldAnalyzer(RobotCameraView robotCameraView)
    : m_robotCameraView{std::move(robotCameraView)}
{

}

void ScaffoldAnalyzer::traverse()
{
    while (true)
    {
        turnIfNeeded();
        stepForward();

        if (getNeighborScaffolds(m_robotCameraView.robotPosition).size() == 1)
        {
            m_journeySteps.push_back(std::to_string(m_stepsInStraightLine));
            break;
        }
    }
}

int ScaffoldAnalyzer::getSumOfAlignmentParameters() const
{
    int sum = 0;

    for (const auto& scaffold : m_robotCameraView.scaffolds)
    {
        std::vector<Coordinates> neighborScaffolds = getNeighborScaffolds(scaffold);
        if (neighborScaffolds.size() == 4)
        {
            sum += (scaffold.first * scaffold.second);
        }
    }

    return sum;
}

std::vector<std::string> ScaffoldAnalyzer::getJourneySteps() const
{
    return m_journeySteps;
}

void ScaffoldAnalyzer::turnIfNeeded()
{
    if (isForwardPathObstructed())
    {
        if (m_stepsInStraightLine != 0)
        {
            m_journeySteps.push_back(std::to_string(m_stepsInStraightLine));
            m_stepsInStraightLine = 0;
        }

        turnLeft();
        if (!isForwardPathObstructed())
        {
            m_journeySteps.push_back("L");
        }
        else
        {
            turnLeft();
            turnLeft();
            assert(!isForwardPathObstructed());
            m_journeySteps.push_back("R");
        }
    }
}

void ScaffoldAnalyzer::turnLeft()
{
    switch (m_robotCameraView.robotDirection)
    {
        case Direction::LEFT:
            m_robotCameraView.robotDirection = Direction::DOWN;
            break;
        case Direction::RIGHT:
            m_robotCameraView.robotDirection = Direction::UP;
            break;
        case Direction::UP:
            m_robotCameraView.robotDirection = Direction::LEFT;
            break;
        case Direction::DOWN:
            m_robotCameraView.robotDirection = Direction::RIGHT;
            break;
        default:
            throw std::runtime_error("Invalid direction");
    }
}

void ScaffoldAnalyzer::stepForward()
{
    assert(!isForwardPathObstructed());
    m_robotCameraView.robotPosition = getCoordinatesInFront();
    ++m_stepsInStraightLine;
}

std::vector<Coordinates> ScaffoldAnalyzer::getNeighborScaffolds(const Coordinates& coordinates) const
{
    std::vector<Coordinates> neighbors
    {
        {coordinates.first - 1, coordinates.second},
        {coordinates.first + 1, coordinates.second},
        {coordinates.first, coordinates.second - 1},
        {coordinates.first, coordinates.second + 1},
    };

    neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(), [this](const auto& coord)
                                   {
                                       return this->m_robotCameraView.scaffolds.find(coord) == this->m_robotCameraView.scaffolds.cend();
                                   }), neighbors.end());

    return neighbors;
}

bool ScaffoldAnalyzer::isForwardPathObstructed() const
{
    Coordinates coordinatesInFront = getCoordinatesInFront();
    return m_robotCameraView.scaffolds.find(coordinatesInFront) == m_robotCameraView.scaffolds.cend();
}

Coordinates ScaffoldAnalyzer::getCoordinatesInFront() const
{
    switch (m_robotCameraView.robotDirection)
    {
        case Direction::LEFT:
            return {m_robotCameraView.robotPosition.first - 1, m_robotCameraView.robotPosition.second};
        case Direction::RIGHT:
            return {m_robotCameraView.robotPosition.first + 1, m_robotCameraView.robotPosition.second};
        case Direction::UP:
            return {m_robotCameraView.robotPosition.first, m_robotCameraView.robotPosition.second - 1};
        case Direction::DOWN:
            return {m_robotCameraView.robotPosition.first, m_robotCameraView.robotPosition.second + 1};
        default:
            throw std::runtime_error("Invalid direction");
    }
}

}
}
}
