#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day22
{

using Coordinates = std::pair<unsigned, unsigned>;

class CaveMap
{
public:
    CaveMap(unsigned depth, Coordinates targetCoordinates);

    unsigned calculateRiskLevelOfArea();
    unsigned getRiskLevelAt(const Coordinates& coordinates);
    const Coordinates& getTargetCoordinates() const;

private:
    using CoordinatesToErosionLevel = std::unordered_map<Coordinates, unsigned, boost::hash<Coordinates>>;

    unsigned m_depth;
    Coordinates m_targetCoordinates;

    CoordinatesToErosionLevel m_erosionLevelCache;

    unsigned getErosionLevelAt(const Coordinates& coordinates);
    unsigned calculateErosionLevelAt(const Coordinates& coordinates);
};

}
}
}
