#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day16
{

using Coordinates = std::pair<int, int>;

const Coordinates STARTING_POSITION{0, 0};
const Coordinates LEFT{-1, 0};
const Coordinates RIGHT{1, 0};
const Coordinates UP{0, -1};
const Coordinates DOWN{0, 1};

struct BeamHead
{
    Coordinates position;
    Coordinates direction;

    BeamHead(Coordinates position, Coordinates direction)
        : position{std::move(position)}
        , direction{std::move(direction)}
    {

    }

    bool operator==(const BeamHead& other) const
    {
        return position == other.position &&
            direction == other.direction;
    }
};

struct BeamHeadHash
{
    std::size_t operator()(const BeamHead& beamHead) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, beamHead.position);
        boost::hash_combine(seed, beamHead.direction);

        return seed;
    }
};

class ContraptionAnalyzer
{
public:
    ContraptionAnalyzer(const std::vector<std::string>& map);

    void shootBeamFrom(const BeamHead& beamHead);

    int getNumEnergizedTiles() const;

private:
    const std::vector<std::string> m_map;

    std::vector<BeamHead> m_beamHeads;
    std::unordered_set<BeamHead, BeamHeadHash> m_visited;

    void processAllBeamHeads();

    std::vector<BeamHead> getNewBeamHeadsFor(const BeamHead& currentBeamHead) const;

    static std::vector<Coordinates> getDirectionsForTile(char tile, const Coordinates& currentDirection);
    static std::vector<Coordinates> getDirectionsForMainDiagonalMirror(const Coordinates& currentDirection);
    static std::vector<Coordinates> getDirectionsForSecondaryDiagonalMirror(const Coordinates& currentDirection);
    static std::vector<Coordinates> getDirectionsForVerticalSplitter(const Coordinates& currentDirection);
    static std::vector<Coordinates> getDirectionsForHorizontalSplitter(const Coordinates& currentDirection);
};

}
}
}
