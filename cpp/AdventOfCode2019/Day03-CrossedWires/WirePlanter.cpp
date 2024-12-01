#include "WirePlanter.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day03
{

WirePlanter::WirePlanter(std::vector<Wire> wires)
    : m_wires{std::move(wires)}
{

}

void WirePlanter::plant()
{
    WireID id = 0;

    for (const auto& wire : m_wires)
    {
        Coordinates currentCoordinates{0, 0};
        unsigned numWireSteps = 0;

        for (const auto& wireSection : wire.wireSections)
        {
            for (size_t i = 0; i < wireSection.length; ++i)
            {
                ++numWireSteps;

                currentCoordinates = getNeighborCoordinates(currentCoordinates, wireSection.direction);

                bool isNotSelfIntersection = m_coordinatesToWires[currentCoordinates].wires.insert(id).second;
                if (isNotSelfIntersection)
                {
                    m_coordinatesToWires[currentCoordinates].numTotalWireSteps += numWireSteps;
                }
            }
        }

        ++id;
    }
}

int WirePlanter::getDistanceToClosestIntersection() const
{
    std::vector<Coordinates> allIntersectionCoordinates = getAllIntersectionCoordinates();

    auto minDistanceCoordinates = *std::min_element(allIntersectionCoordinates.cbegin(), allIntersectionCoordinates.cend(), [](const auto& lhs, const auto& rhs) noexcept
                                                    {
                                                        return std::abs(lhs.first) + std::abs(lhs.second) < std::abs(rhs.first) + std::abs(rhs.second);
                                                    });

    return std::abs(minDistanceCoordinates.first) + std::abs(minDistanceCoordinates.second);
}

int WirePlanter::getCombinedWireStepsToClosestIntersection() const
{
    std::vector<Coordinates> allIntersectionCoordinates = getAllIntersectionCoordinates();

    auto minCombinedWireStepsCoordinates = *std::min_element(allIntersectionCoordinates.cbegin(), allIntersectionCoordinates.cend(), [this](const auto& lhs, const auto& rhs)
                                                                {
                                                                    const auto& lhsFieldWireInfo = this->m_coordinatesToWires.at(lhs);
                                                                    const auto& rhsFieldWireInfo = this->m_coordinatesToWires.at(rhs);
                                                                    return lhsFieldWireInfo.numTotalWireSteps < rhsFieldWireInfo.numTotalWireSteps;
                                                                });

    return m_coordinatesToWires.at(minCombinedWireStepsCoordinates).numTotalWireSteps;
}

std::vector<WirePlanter::Coordinates> WirePlanter::getAllIntersectionCoordinates() const
{
    std::vector<Coordinates> allIntersectionCoordinates;

    for (const auto& coordinatesAndWires : m_coordinatesToWires)
    {
        if (coordinatesAndWires.second.wires.size() > 1)
        {
            allIntersectionCoordinates.push_back(coordinatesAndWires.first);
        }
    }

    return allIntersectionCoordinates;
}

WirePlanter::Coordinates WirePlanter::getNeighborCoordinates(const WirePlanter::Coordinates& coordinates, Direction direction)
{
    switch (direction)
    {
        case Direction::UP:
            return Coordinates{coordinates.first, coordinates.second - 1};
        case Direction::DOWN:
            return Coordinates{coordinates.first, coordinates.second + 1};
        case  Direction::LEFT:
            return Coordinates{coordinates.first - 1, coordinates.second};
        case Direction::RIGHT:
            return Coordinates{coordinates.first + 1, coordinates.second};
    }

    throw std::runtime_error("Unknown direction: " + std::to_string(static_cast<int>(direction)));
}

}
}
}
