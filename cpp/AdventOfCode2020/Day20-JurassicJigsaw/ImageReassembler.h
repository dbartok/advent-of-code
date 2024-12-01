#pragma once

#include "Tile.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day20
{

enum class Direction
{
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3,
};

class ImageReassembler
{
public:
    ImageReassembler(std::vector<Tile> scrambledTiles);

    void reassemble();

    int64_t getCornerTileIDsMultiplied() const;
    std::vector<Image> getAllPossibleImages() const;

private:
    std::vector<Tile> m_scrambledTiles;
    size_t m_reassembledImageLengthInTiles;
    std::vector<std::vector<Tile>> m_reassembledTileGrid;

    void populateTopLeftCorner();
    void populateSubsequentTiles();
    void populateTileAt(size_t i, size_t j);
    void removeBorders();

    bool isTileVariantTopLeftCorner(const Tile& tileVariant) const;
    std::vector<Tile> findAllPossibleNeighborsInDirection(const Tile& anchorTileVariant, Direction direction) const;
    bool doesTileVariantFitAnchorInDirection(Tile anchorTileVariant, Tile tileVariant, Direction direction) const;
    bool doesTileVariantFitAnchorToUpwards(const Tile& anchorTileVariant, const Tile& tileVariant) const;
    boost::optional<std::vector<Tile>> getPossibleTilesFromUpwardsConstraint(size_t x, size_t y) const;
    boost::optional<std::vector<Tile>> getPossibleTilesFromLeftwardsConstraint(size_t x, size_t y) const;

    Tile resolveTileFromMaybeConstraints(const boost::optional<std::vector<Tile>>& possibleTilesFromUpwardsConstraint,
                                         const boost::optional<std::vector<Tile>>& possibleTilesFromLeftwardsConstraint) const;

    Tile resolveTileFromBothConstraints(std::vector<Tile> possibleTilesFromUpwardsConstraint,
                                        std::vector<Tile> possibleTilesFromLeftwardsConstraint) const;

    Tile getAllTilesCombined() const;
};

}
}
}
