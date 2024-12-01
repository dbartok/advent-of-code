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
namespace Day24
{

const size_t GRID_SIZE = 5;

using Coordinates = std::pair<int, int>;

struct LeveledCoordinates
{
    LeveledCoordinates(int level, Coordinates coordinates)
        : level{level}
        , coordinates{std::move(coordinates)}
    {

    }

    int level;
    Coordinates coordinates;

    bool operator==(const LeveledCoordinates& other) const
    {
        return level == other.level && coordinates == other.coordinates;
    }
};

struct LeveledCoordinatesHash
{
    std::size_t operator()(const LeveledCoordinates& lc) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, lc.level);
        boost::hash_combine(seed, lc.coordinates);

        return seed;
    }
};

using Layout = std::unordered_set<LeveledCoordinates, LeveledCoordinatesHash>;
using Layouts = std::vector<Layout>;

class BugCellularAutomaton
{
public:
    BugCellularAutomaton(Layout initialLayout, size_t size);

    void simulateUntilFirstDuplicate();
    void simulateStepsRecursiveGrid(unsigned numSteps);

    int getCurrentBiodiversity() const;
    unsigned getNumBugs();

private:
    Layout m_currentLayout;
    size_t m_size;

    Layouts m_previousLayouts;

    void executeSimulationStep();
    void executeSimulationStepRecursiveGrid();

    unsigned getNumSurroundingBugs(const LeveledCoordinates& currentCoordinates) const;
    unsigned getNumSurroundingBugsRecursive(const LeveledCoordinates& currentCoordinates) const;

    std::vector<LeveledCoordinates> getSameLevelNeighbors(const LeveledCoordinates& currentCoordinates) const;
    std::vector<LeveledCoordinates> getNextLevelNeighbors(const LeveledCoordinates& currentCoordinates) const;
    std::vector<LeveledCoordinates> getPrevLevelNeighbors(const LeveledCoordinates& currentCoordinates) const;

    unsigned numberOfBugs(const std::vector<LeveledCoordinates>& allPossibleCoordinates) const;
    bool isBugInNextIteration(const LeveledCoordinates& leveledCoordinates, unsigned numSurroundingBugs) const;
    std::pair<int, int> getLevelBounds() const;

    static void addAllCoordsAtGivenLevel(std::vector<LeveledCoordinates>& destination, const std::vector<Coordinates>& source, int level);
};

}
}
}
