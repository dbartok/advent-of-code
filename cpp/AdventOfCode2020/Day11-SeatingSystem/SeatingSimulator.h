#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>

#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day11
{

using Vector2D = Eigen::Matrix<int, 2, 1>;

using SeatState = char;
const SeatState FLOOR = '.';
const SeatState EMPTY_SEAT = 'L';
const SeatState OCCUPIED_SEAT = '#';

using SeatStateRow = std::string;
using SeatLayout = std::vector<SeatStateRow>;

class SeatingSimulator
{
public:
    SeatingSimulator(std::vector<std::string> seatLayoutLines, size_t visionRange, size_t numVisibleOccupiedSeatsThreshold);

    void simulateUntilStable();

    int getNumOccupiedSeats() const;

private:
    SeatLayout m_seatLayout;
    const size_t m_visionRange;
    const size_t m_numVisibleOccupiedSeatsThreshold;
    const size_t m_width;
    const size_t m_height;

    SeatLayout getNextLayout() const;
    SeatState getNextStateAt(int x, int y) const;
    int getNumVisibleOccupiedSeatsFrom(int x, int y) const;
    bool isOccupiedSeatVisibleInGivenDirectionFrom(int x, int y, const Vector2D& directionVector) const;
    bool isOutOfBounds(int x, int y) const;

    static std::vector<Vector2D> getAllDirectionVectors();
};

}
}
}
