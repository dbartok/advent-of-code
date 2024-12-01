#include "BugCellularAutomaton.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <cmath>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day24
{

Coordinates midpoint(size_t size)
{
    return {size / 2, size / 2};
}

Coordinates leftFromMidpoint(size_t size)
{
    Coordinates mp = midpoint(size);
    return {mp.first - 1, mp.second};
}

Coordinates rightFromMidpoint(size_t size)
{
    Coordinates mp = midpoint(size);
    return {mp.first + 1, mp.second};
}

Coordinates upFromMidpoint(size_t size)
{
    Coordinates mp = midpoint(size);
    return {mp.first, mp.second - 1};
}

Coordinates downFromMidpoint(size_t size)
{
    Coordinates mp = midpoint(size);
    return {mp.first, mp.second + 1};
}

std::vector<Coordinates> leftEdge(size_t size)
{
    std::vector<Coordinates> coords;
    for (int j = 0; j < size; ++j)
    {
        coords.emplace_back(0, j);
    }
    return coords;
}

std::vector<Coordinates> rightEdge(size_t size)
{
    std::vector<Coordinates> coords;
    for (int j = 0; j < size; ++j)
    {
        coords.emplace_back(size - 1, j);
    }
    return coords;
}

std::vector<Coordinates> topEdge(size_t size)
{
    std::vector<Coordinates> coords;
    for (int i = 0; i < size; ++i)
    {
        coords.emplace_back(i, 0);
    }
    return coords;
}

std::vector<Coordinates> bottomEdge(size_t size)
{
    std::vector<Coordinates> coords;
    for (int i = 0; i < size; ++i)
    {
        coords.emplace_back(i, size - 1);
    }
    return coords;
}

BugCellularAutomaton::BugCellularAutomaton(Layout initialLayout, size_t size)
    : m_currentLayout{std::move(initialLayout)}
    , m_size{size}
{

}

void BugCellularAutomaton::simulateUntilFirstDuplicate()
{
    while (std::find(m_previousLayouts.cbegin(), m_previousLayouts.cend(), m_currentLayout) == m_previousLayouts.cend())
    {
        m_previousLayouts.push_back(m_currentLayout);
        executeSimulationStep();
    }
}

void BugCellularAutomaton::simulateStepsRecursiveGrid(unsigned numSteps)
{
    for (size_t i = 0; i < numSteps; ++i)
    {
        executeSimulationStepRecursiveGrid();
    }
}

int BugCellularAutomaton::getCurrentBiodiversity() const
{
    int biodiversity = 0;

    for (int j = 0; j < m_size; ++j)
    {
        for (int i = 0; i < m_size; ++i)
        {
            if (m_currentLayout.find({0, {i, j}}) != m_currentLayout.cend())
            {
                biodiversity += std::pow(2, j * m_size + i);
            }
        }
    }

    return biodiversity;
}

unsigned BugCellularAutomaton::getNumBugs()
{
    return m_currentLayout.size();
}

void BugCellularAutomaton::executeSimulationStep()
{
    Layout nextLayout;

    for (int j = 0; j < m_size; ++j)
    {
        for (int i = 0; i < m_size; ++i)
        {
            LeveledCoordinates currentCoordinates{0, {i, j}};
            int numSurroundingBugs = getNumSurroundingBugs(currentCoordinates);
            if (isBugInNextIteration(currentCoordinates, numSurroundingBugs))
            {
                nextLayout.insert(std::move(currentCoordinates));
            }
        }
    }

    m_currentLayout = nextLayout;
}

void BugCellularAutomaton::executeSimulationStepRecursiveGrid()
{
    Layout nextLayout;

    std::pair<int, int> levelBounds = getLevelBounds();

    for (int level = levelBounds.first - 1; level <= levelBounds.second + 1; ++level)
    {
        for (int j = 0; j < m_size; ++j)
        {
            for (int i = 0; i < m_size; ++i)
            {
                if (Coordinates{i, j} == midpoint(GRID_SIZE))
                {
                    continue;
                }

                LeveledCoordinates currentCoordinates{level, {i, j}};
                int numSurroundingBugs = getNumSurroundingBugsRecursive(currentCoordinates);
                if (isBugInNextIteration(currentCoordinates, numSurroundingBugs))
                {
                    nextLayout.insert(std::move(currentCoordinates));
                }
            }
        }
    }

    m_currentLayout = nextLayout;
}

unsigned BugCellularAutomaton::getNumSurroundingBugs(const LeveledCoordinates& currentCoordinates) const
{
    auto neighborCoordinates = getSameLevelNeighbors(currentCoordinates);
    return numberOfBugs(neighborCoordinates);
}

unsigned BugCellularAutomaton::getNumSurroundingBugsRecursive(const LeveledCoordinates& currentCoordinates) const
{
    std::vector<LeveledCoordinates> allNeighborCoordinates = getSameLevelNeighbors(currentCoordinates);

    std::vector<LeveledCoordinates> nextLevelNeighborCoordinates = getNextLevelNeighbors(currentCoordinates);
    allNeighborCoordinates.insert(allNeighborCoordinates.end(), nextLevelNeighborCoordinates.begin(), nextLevelNeighborCoordinates.end());

    std::vector<LeveledCoordinates> prevLevelNeighborCoordinates = getPrevLevelNeighbors(currentCoordinates);
    allNeighborCoordinates.insert(allNeighborCoordinates.end(), prevLevelNeighborCoordinates.begin(), prevLevelNeighborCoordinates.end());

    return numberOfBugs(allNeighborCoordinates);
}

std::vector<LeveledCoordinates> BugCellularAutomaton::getSameLevelNeighbors(const LeveledCoordinates& currentCoordinates) const
{
    std::vector<LeveledCoordinates> neighbors;
    int level = currentCoordinates.level;
    int x, y;
    std::tie(x, y) = currentCoordinates.coordinates;
    neighbors.emplace_back(level, Coordinates{x + 1, y});
    neighbors.emplace_back(level, Coordinates{x - 1, y});
    neighbors.emplace_back(level, Coordinates{x, y + 1});
    neighbors.emplace_back(level, Coordinates{x, y - 1});
    return neighbors;
}

std::vector<LeveledCoordinates> BugCellularAutomaton::getNextLevelNeighbors(const LeveledCoordinates& currentCoordinates) const
{
    std::vector<LeveledCoordinates> neighbors;
    int level = currentCoordinates.level;
    const Coordinates& coordinates = currentCoordinates.coordinates;

    if (coordinates == leftFromMidpoint(GRID_SIZE))
    {
        addAllCoordsAtGivenLevel(neighbors, leftEdge(GRID_SIZE), level + 1);
    }

    if (coordinates == rightFromMidpoint(GRID_SIZE))
    {
        addAllCoordsAtGivenLevel(neighbors, rightEdge(GRID_SIZE), level + 1);
    }

    if (coordinates == upFromMidpoint(GRID_SIZE))
    {
        addAllCoordsAtGivenLevel(neighbors, topEdge(GRID_SIZE), level + 1);
    }

    if (coordinates == downFromMidpoint(GRID_SIZE))
    {
        addAllCoordsAtGivenLevel(neighbors, bottomEdge(GRID_SIZE), level + 1);
    }

    return neighbors;
}

std::vector<LeveledCoordinates> BugCellularAutomaton::getPrevLevelNeighbors(const LeveledCoordinates& currentCoordinates) const
{
    std::vector<LeveledCoordinates> neighbors;
    int level = currentCoordinates.level;
    const Coordinates& coordinates = currentCoordinates.coordinates;

    auto leftEdgePoints = leftEdge(GRID_SIZE);
    if (std::find(leftEdgePoints.cbegin(), leftEdgePoints.cend(), coordinates) != leftEdgePoints.cend())
    {
        neighbors.emplace_back(level - 1, leftFromMidpoint(GRID_SIZE));
    }

    auto rightEdgePoints = rightEdge(GRID_SIZE);
    if (std::find(rightEdgePoints.cbegin(), rightEdgePoints.cend(), coordinates) != rightEdgePoints.cend())
    {
        neighbors.emplace_back(level - 1, rightFromMidpoint(GRID_SIZE));
    }

    auto topEdgePoints = topEdge(GRID_SIZE);
    if (std::find(topEdgePoints.cbegin(), topEdgePoints.cend(), coordinates) != topEdgePoints.cend())
    {
        neighbors.emplace_back(level - 1, upFromMidpoint(GRID_SIZE));
    }

    auto bottomEdgePoints = bottomEdge(GRID_SIZE);
    if (std::find(bottomEdgePoints.cbegin(), bottomEdgePoints.cend(), coordinates) != bottomEdgePoints.cend())
    {
        neighbors.emplace_back(level - 1, downFromMidpoint(GRID_SIZE));
    }

    return neighbors;
}

unsigned BugCellularAutomaton::numberOfBugs(const std::vector<LeveledCoordinates>& allPossibleCoordinates) const
{
    return std::count_if(allPossibleCoordinates.cbegin(), allPossibleCoordinates.cend(), [this](const auto& coords)
                         {
                             return this->m_currentLayout.find(coords) != this->m_currentLayout.cend();
                         });
}

bool BugCellularAutomaton::isBugInNextIteration(const LeveledCoordinates& currentCoordinates, unsigned numSurroundingBugs) const
{
    bool isBug = m_currentLayout.find(currentCoordinates) != m_currentLayout.cend();
    if (isBug)
    {
        return numSurroundingBugs == 1;
    }
    else
    {
        return numSurroundingBugs == 1 || numSurroundingBugs == 2;
    }
}

std::pair<int, int> BugCellularAutomaton::getLevelBounds() const
{
    auto minmaxLevelLeveledCoordsIterPair = std::minmax_element(m_currentLayout.cbegin(), m_currentLayout.cend(), [](const auto& lhs, const auto& rhs)
                                                                {
                                                                    return lhs.level < rhs.level;
                                                                });

    const auto& minLevelLeveledCoords = *minmaxLevelLeveledCoordsIterPair.first;
    const auto& maxLevelLeveledCoords = *minmaxLevelLeveledCoordsIterPair.second;
    const int minLevel = minLevelLeveledCoords.level;
    const int maxLevel = maxLevelLeveledCoords.level;

    return {minLevel, maxLevel};
}

void BugCellularAutomaton::addAllCoordsAtGivenLevel(std::vector<LeveledCoordinates>& destination, const std::vector<Coordinates>& source, int level)
{
    for (const auto& coords : source)
    {
        destination.emplace_back(level, coords);
    }
}

}
}
}
