#include "SeatingSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day11
{

SeatingSimulator::SeatingSimulator(std::vector<std::string> seatLayoutLines, size_t visionRange, size_t numVisibleOccupiedSeatsThreshold)
    : m_seatLayout{std::move(seatLayoutLines)}
    , m_visionRange{visionRange}
    , m_numVisibleOccupiedSeatsThreshold{numVisibleOccupiedSeatsThreshold}
    , m_width{m_seatLayout.at(0).size()}
    , m_height{m_seatLayout.size()}
{

}

void SeatingSimulator::simulateUntilStable()
{
    while (true)
    {
        SeatLayout nextLayout = getNextLayout();
        if (nextLayout == m_seatLayout)
        {
            break;
        }
        m_seatLayout = std::move(nextLayout);
    }
}

int SeatingSimulator::getNumOccupiedSeats() const
{
    int numOccupiedSeats = 0;

    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            if (m_seatLayout.at(j).at(i) == OCCUPIED_SEAT)
            {
                ++numOccupiedSeats;
            }
        }
    }

    return numOccupiedSeats;
}

SeatLayout SeatingSimulator::getNextLayout() const
{
    auto nextLayout{m_seatLayout};

    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            nextLayout.at(j).at(i) = getNextStateAt(i, j);
        }
    }

    return nextLayout;
}

SeatState SeatingSimulator::getNextStateAt(int x, int y) const
{
    const SeatState currentState = m_seatLayout.at(y).at(x);

    if (currentState == FLOOR)
    {
        return FLOOR;
    }

    const int numOccupiedVisibleSeats = getNumVisibleOccupiedSeatsFrom(x, y);

    if (currentState == EMPTY_SEAT && numOccupiedVisibleSeats == 0)
    {
        return OCCUPIED_SEAT;
    }

    if (currentState == OCCUPIED_SEAT && numOccupiedVisibleSeats >= m_numVisibleOccupiedSeatsThreshold)
    {
        return EMPTY_SEAT;
    }

    return currentState;
}

int SeatingSimulator::getNumVisibleOccupiedSeatsFrom(int x, int y) const
{
    int numOccupiedNeighbors = 0;

    for (const auto& directionVector : getAllDirectionVectors())
    {
        if (isOccupiedSeatVisibleInGivenDirectionFrom(x, y, directionVector))
        {
            ++numOccupiedNeighbors;
        }
    }

    return numOccupiedNeighbors;
}

bool SeatingSimulator::isOccupiedSeatVisibleInGivenDirectionFrom(int x, int y, const Vector2D& directionVector) const
{
    Vector2D positionVector{x, y};
    for (size_t i = 0; i < m_visionRange; ++i)
    {
        positionVector += directionVector;

        if (isOutOfBounds(positionVector[0], positionVector[1]))
        {
            return false;
        }

        if (m_seatLayout.at(positionVector[1]).at(positionVector[0]) == OCCUPIED_SEAT)
        {
            return true;
        }

        if (m_seatLayout.at(positionVector[1]).at(positionVector[0]) == EMPTY_SEAT)
        {
            return false;
        }
    }

    return false;
}

bool SeatingSimulator::isOutOfBounds(int x, int y) const
{
    return x < 0 || x >= m_width || y < 0 || y >= m_height;
}

std::vector<Vector2D> SeatingSimulator::getAllDirectionVectors()
{
    return std::vector<Vector2D>
    {
        Vector2D{1, 0},
        Vector2D{-1, 0},
        Vector2D{0, 1},
        Vector2D{0, -1},
        Vector2D{1, 1},
        Vector2D{-1, 1},
        Vector2D{-1, -1},
        Vector2D{1, -1},
    };
}

}
}
}
