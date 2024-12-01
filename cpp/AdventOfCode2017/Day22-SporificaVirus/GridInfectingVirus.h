#pragma once

#include <AdventOfCode2017/Day03-SpiralMemory/InfiniteGrid.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day22
{

using AdventOfCode::Year2017::Day03::InfiniteGrid;

enum class InfectionState
{
    CLEAN = 0,
    WEAKENED = 1,
    INFECTED = 2,
    FLAGGED = 3
};

class GridInfectingVirus
{
public:
    GridInfectingVirus(InfiniteGrid<InfectionState> initialGrid);

    GridInfectingVirus(const GridInfectingVirus&) = default;
    GridInfectingVirus(GridInfectingVirus&&) = default;
    GridInfectingVirus& operator=(const GridInfectingVirus&) = default;
    GridInfectingVirus& operator=(GridInfectingVirus&&) = default;
    virtual ~GridInfectingVirus() = default;

    void infectRepeatedly(unsigned numIterations);
    unsigned getTotalInfectionBursts() const noexcept;

protected:
    InfiniteGrid<InfectionState> m_grid;

    enum class Direction
    {
        LEFT = 0,
        UP = 1,
        RIGHT = 2,
        DOWN = 3,
        _MODULUS = 4
    };

    Direction m_direction;
    std::pair<int, int> m_coords;

    unsigned m_totalInfectionBursts;

    virtual void makeInfectionStep() = 0;

    void turnLeft() noexcept;
    void turnRight() noexcept;
    void reverseDirection() noexcept;
    void stepForward() noexcept;
};


class BasicGridInfectingVirus : public GridInfectingVirus
{
public:
    using GridInfectingVirus::GridInfectingVirus;

    BasicGridInfectingVirus(const BasicGridInfectingVirus&) = default;
    BasicGridInfectingVirus(BasicGridInfectingVirus&&) = default;
    BasicGridInfectingVirus& operator=(const BasicGridInfectingVirus&) = default;
    BasicGridInfectingVirus& operator=(BasicGridInfectingVirus&&) = default;
    ~BasicGridInfectingVirus() = default;

protected:
    void makeInfectionStep() override;
};

class EvolvedGridInfectingVirus : public GridInfectingVirus
{
public:
    using GridInfectingVirus::GridInfectingVirus;

    EvolvedGridInfectingVirus(const EvolvedGridInfectingVirus&) = default;
    EvolvedGridInfectingVirus(EvolvedGridInfectingVirus&&) = default;
    EvolvedGridInfectingVirus& operator=(const EvolvedGridInfectingVirus&) = default;
    EvolvedGridInfectingVirus& operator=(EvolvedGridInfectingVirus&&) = default;
    ~EvolvedGridInfectingVirus() = default;

protected:
    void makeInfectionStep() override;
};

}
}
}
