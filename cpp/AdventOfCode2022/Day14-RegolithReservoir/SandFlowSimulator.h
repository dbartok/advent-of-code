#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>
#include <boost/functional/hash.hpp>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day14
{

using Coordinates = std::pair<int, int>;
using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

const int SIMULATION_BOUNDARY_COORDINATE = 1'000;

class SandFlowSimulator
{
public:
    SandFlowSimulator(CoordinatesSet allRockCoordinates);

    void simulate();

    unsigned getNumSettledUnits() const;

private:
    CoordinatesSet m_allOccupiedCoordinates;

    unsigned m_numSettledUnits = 0;

    bool trySettleNextSandParticle();

    boost::optional<Coordinates> getNextSandCoordinates(const Coordinates& currentCoordinates) const;
};


}
}
}
